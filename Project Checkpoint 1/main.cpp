#include "Color.h"
#include "Raster.h"
#include "Vector.h"
#include "Triangle.h"
#include "Matrix.h"
#include "Model.h"

#include <iostream>
using namespace std;

#define WIDTH 100
#define HEIGHT 100

int main() {
	/*
	Raster myRaster(10, 10, White);
	myRaster.drawLine_DDA(5, 0, 0, 0, Red);
	myRaster.writeToPPM();
	*/

	/*
	Matrix4 A(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

	Matrix4 B(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);

	Matrix4 C = A * B;

	C.print();
	*/

	
	/*
	Raster myRaster(100, 100, White);
	Triangle3D t(Vector4(0, 0, 0, 1), Vector4(40, 0, 0, 1), Vector4(40, 40, 0, 1), Red, Blue, Green);
	t.shouldDraw = true;
	myRaster.drawTriangle3D_Barycentric(t);
	myRaster.writeToPPM();

	return 0;
	*/

	/*
	Raster myRaster(100, 100, White);
	Triangle3D t(Vector4(0, 0, 0, 1), Vector4(40, 0, 0, 1), Vector4(40, 40, 0, 1), Red, Blue, Green);

	Matrix4 m = RotateX3D(-45.0);
	t.transform(m);

	myRaster.drawTriangle3D_Barycentric(t);
	myRaster.writeToPPM();

	return 0;
	*/

	/*
	Raster myRaster(100, 100, White);
	Model teapot = Model();
	teapot.readfromObj("./teapot.obj", Red);

	Matrix4 m = Translate3D(50, 50, 0) * RotateZ3D(-45.0) * Scale3D(0.5, 0.5, 0.5);
	teapot.transform(m);

	myRaster.drawModel(teapot);

	myRaster.writeToPPM();

	return 0;
	*/
	
	
	Raster myRaster(WIDTH, HEIGHT, White);

	Model teapot, bunny;
	teapot.readfromObj("./teapot.obj", Red);
	bunny.readfromObj("./bunny.obj", Blue);

	Matrix4 modelMatirixTeapot = Translate3D(50, 50, -60) * RotateZ3D(45.0) * Scale3D(0.5, 0.5, 0.5);
	Matrix4 modelMatirixBunny = Translate3D(70, 30, -60) * RotateZ3D(-20.0) * Scale3D(500, 500, 500);

	teapot.performBackfaceCulling(Vector4(50, 50, 30, 1), Vector4(50, 50, -40, 1));
	bunny.performBackfaceCulling(Vector4(50, 50, 30, 1), Vector4(50, 50, -40, 1));

	Matrix4 viewMatrix = LookAt(Vector4(50, 50, 30, 1), Vector4(50, 50, -40, 1), Vector4(0, 1, 0, 0));

	Matrix4 perspectiveMatrix = Perspective(70.0, myRaster.getWidth() / myRaster.getHeight(), 0.01, 1000.0);

	Matrix4 viewportMatrix = Viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

	teapot.transform(perspectiveMatrix * viewMatrix * modelMatirixTeapot);
	bunny.transform(perspectiveMatrix * viewMatrix * modelMatirixBunny);

	teapot.homogenize();
	bunny.homogenize();

	teapot.transform(viewportMatrix);
	bunny.transform(viewportMatrix);

	myRaster.drawModel(teapot);
	myRaster.drawModel(bunny);

	myRaster.writeToPPM();
	
 
	/*
	Raster myRaster(WIDTH, HEIGHT, White);

	Model teapot;
	teapot.readfromObj("./teapot.obj", Red);

	Matrix4 modelMatrixTeapot = Translate3D(50, 50, -30) * RotateZ3D(45.0) * Scale3D(0.5, 0.5, 0.5);

	
	Vector4 eye(50, 50, 30, 1);
	Vector4 spot(50, 50, -30, 1);
	teapot.performBackfaceCulling(eye, spot);
	
	Matrix4 viewMatrix = LookAt(eye, spot, Vector4(0, 1, 0, 0));

	Matrix4 perspectiveMatrix = Perspective(70.0, myRaster.getWidth() / myRaster.getHeight(), 0.01, 88.5);


	Matrix4 viewportMatrix = Viewport(0, 0, myRaster.getWidth(), myRaster.getHeight());

	teapot.transform(perspectiveMatrix * viewMatrix * modelMatrixTeapot);

	
	teapot.homogenize();
	
	teapot.transform(viewportMatrix);

	myRaster.drawModel(teapot);

	myRaster.writeToPPM();
	*/
	
}

