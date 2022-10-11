#include <iostream>
#include "Raster.h"
#include "Color.h"
#include <cmath>
#include <algorithm>
#include <fstream>
#include <limits>
using namespace std;


	Raster::Raster() {
		width = 0;
		height = 0;
		pixels = nullptr;
		depthPixels = nullptr;
	}

	Raster::Raster(int pWidth, int pHeight, Color pFillColor) {
		width = pWidth;
		height = pHeight;
		int length = width * height;
		pixels = new Color[length];
		for (int i = 0; i < length; i++) {
			pixels[i] = pFillColor;
		}
		depthPixels = new float[length];
		for (int i = 0; i < length; i++)
		{
			depthPixels[i] = numeric_limits<float>::max();
		}
	}

	Raster::~Raster() {
		delete[] pixels;
		delete[] depthPixels;
	}

	int Raster::getWidth() {
		return width;
	}

	int Raster::getHeight() {
		return height;
	}

	Color Raster::getColorPixel(int x, int y) {
		return pixels[(height - y - 1) * width + x];

	}

	void Raster::setColorPixel(int x, int y, Color pFillColor) {
		if (x < 0 || x > width - 1 || y < 0 || y > height - 1) {
			return;
		}
		pixels[(height - y - 1) * width + x] = pFillColor;
	}

	void Raster::clear(Color pFillColor) {
		for (int i = 0; i < width * height; i++) {
			pixels[i] = pFillColor;
		}
	}

	void Raster::writeToPPM() {
		ofstream ppmFile;
		ppmFile.open("FRAME_BUFFER.ppm");
		ppmFile << "P3\n";
		ppmFile << width << " " << height << "\n";
		ppmFile << 255;
		for (int i = 0; i < width * height; i++) {
			if (i % width == 0) {
				ppmFile << endl;
			}
			ppmFile << (int)(pixels[i].red * 255) << " " << (int)(pixels[i].green * 255) << " " << (int)(pixels[i].blue * 255) << " ";
			
		}
		ppmFile.close(); 
	}

	void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color fillColor) {
		float m;
		if (x1 != x2) {
			m = (y2 - y1) / (x2 - x1);
			if (abs(m) > 1) {
				m = 1 / m;
				if (y2 > y1) {
					swap(x1, x2);
					swap(y1, y2);
				}
				float x = x1;
				for (int y = y1; y >= y2; y--) {
					setColorPixel(round(x), y, fillColor);
					x -= m;
				}
			}
			else {
				if (x1 > x2) {
					swap(x1, x2);
					swap(y1, y2);
				}
				float y = y1;
				for (int x = x1; x <= x2; x++) {
					setColorPixel(x, round(y), fillColor);
					y += m;
				}
			}
		}
		else {
			m = 0;
			if (y2 > y1) {
				swap(x1, x2);
				swap(y1, y2);
			}
			float x = x1;
			for (int y = y1; y >= y2; y--) {
				setColorPixel(round(x), y, fillColor);
				x -= m;
			}
		}
	}

	void Raster::swap(float& x1, float& x2) {
		float copy = x1;
		x1 = x2;
		x2 = copy;
	}

	void Raster::drawLine_DDA_Interpolated(float x1, float y1, float x2, float y2, Color color1, Color color2)
	{
		float m;
		if (x1 != x2) {
			m = (y2 - y1) / (x2 - x1);
			if (abs(m) > 1) {
				m = 1 / m;
				if (y2 > y1) {
					swap(x1, x2);
					swap(y1, y2);
				}
				float x = x1;
				for (int y = y1; y >= y2; y--) {
					Vector2 P(x, y);
					Vector2 vector1(x1, y1);
					Vector2 vector2(x2, y2);
					float ratio = (vector2 - P).magnitude() / (vector2 - vector1).magnitude();
					setColorPixel(round(x), y, color1 * ratio + color2 * (1 - ratio));
					x -= m;
				}
			}
			else {
				if (x1 > x2) {
					swap(x1, x2);
					swap(y1, y2);
				}
				float y = y1;
				for (int x = x1; x <= x2; x++) {
					Vector2 P(x, y);
					Vector2 vector1(x1, y1);
					Vector2 vector2(x2, y2);
					float ratio = (vector2 - P).magnitude() / (vector2 - vector1).magnitude();
					setColorPixel(x, round(y), color1 * ratio + color2 * (1 - ratio));
					y += m;
				}
			}
		}
		else {
			m = 0;
			if (y2 > y1) {
				swap(x1, x2);
				swap(y1, y2);
			}
			float x = x1;
			for (int y = y1; y >= y2; y--) {
				Vector2 P(x, y);
				Vector2 vector1(x1, y1);
				Vector2 vector2(x2, y2);
				float ratio = (vector2 - P).magnitude() / (vector2 - vector1).magnitude();
				setColorPixel(round(x), y, color1 * ratio + color2 * (1 - ratio));
				x -= m;
			}
		}
	}

	void Raster::drawTriangle2D_DotProduct(Triangle2D triangle)
	{
		int xmin = round(fminf(triangle.v1.x, fminf(triangle.v2.x, triangle.v3.x)));
		int xmax = round(fmaxf(triangle.v1.x, fmaxf(triangle.v2.x, triangle.v3.x)));
		int ymin = round(fminf(triangle.v1.y, fminf(triangle.v2.y, triangle.v3.y)));
		int ymax = round(fmaxf(triangle.v1.y, fmaxf(triangle.v2.y, triangle.v3.y)));

		xmin = fmax(0, xmin);
		xmax = fmin(width, xmax);
		ymin = fmax(0, ymin);
		ymax = fmin(height, ymax);

		for(int x = xmin; x < xmax; x++) {
			for (int y = ymin; y <= ymax; y++) {
				if (triangle.inside(x, y)) {
					setColorPixel(x, y, triangle.c1);
				}
			}
		}
	}

	void Raster::drawTriangle3D_Barycentric(Triangle3D triangle)
	{
		if (triangle.shouldDraw == true) {
			Triangle2D T(triangle);
			Vector2 v1 = T.v1;
			Vector2 v2 = T.v2;
			Vector2 v3 = T.v3;

			float f1;
			float f2;
			float f3;

			double xmin = min({ v1.x, v2.x, v3.x });
			double xmax = max({ v1.x, v2.x, v3.x });
			double ymin = min({ v1.y, v2.y, v3.y });
			double ymax = max({ v1.y, v2.y, v3.y });

			for (int x = xmin; x <= xmax; x++) {
				for (int y = ymin; y <= ymax; y++) {
					T.calculateBarycentricCoordinates(Vector2(x, y), f1, f2, f3);
					if (f1 >= 0 && f2 >= 0 && f3 >= 0)
					{
						Color fillColor = (T.c1 * f1) + (T.c2 * f2) + (T.c3 * f3);
						float depth = triangle.v1.z * f1 + triangle.v2.z * f2 + triangle.v3.z * f3;
						if (depth < getDepthPixel(x, y)) {
							setDepthPixel(x, y, depth);
							setColorPixel(x, y, fillColor);
						}
					}
				}
			}
		}
	}

	void Raster::drawModel(Model model)
	{
		for (int i = 0; i < model.numTriangles(); i++)
		{
			Triangle3D t = model[i];
			drawTriangle3D_Barycentric(t);
		}
	}

	float Raster::getDepthPixel(int x, int y)
	{
		if (x < 0 || x > width - 1 || y < 0 || y > height - 1) {
			return 0;
		}
		int temp = height - y - 1;
		int myPixel = temp * width + x;
		return depthPixels[myPixel];
	}

	void Raster::setDepthPixel(int x, int y, float depth)
	{
		if (x < 0 || x > width - 1 || y < 0 || y > height - 1) {
			return;
		}
		int temp = height - y - 1;
		int myPixel = temp * width + x;
		depthPixels[myPixel] = depth;
	}

	void Raster::clear(float depth)
	{
		for (int i = 0; i < width * height; i++)
		{
			depthPixels[i] = depth;
		}
	}