#include <iostream>
#include "Color.h"
using namespace std;


	Color::Color() {
		red = 0.0;
		green = 0.0;
		blue = 0.0;
		alpha = 255.0;
	}
	
	Color::Color(float pRed, float pGreen, float pBlue, float pAlpha) {

		red = pRed;
		green = pGreen;
		blue = pBlue;
		alpha = pAlpha;
		Clamp();
	}

	void Color::Clamp() {
		float LOWER = 0.0;
		float HIGHER = 1.0;

		if (red < LOWER) {
			red = 0.0;
		}
		else if (red > HIGHER) {
			red = 1.0;
		}
		if (green < LOWER) {
			green = 0.0;
		}
		else if (green > HIGHER) {
			green = 1.0;
		}
		if (blue < LOWER) {
			blue = 0.0;
		}
		else if (blue > HIGHER) {
			blue = 1.0;
		}
		if (alpha < LOWER) {
			alpha = 0.0;
		}
		else if (alpha > HIGHER) {
			alpha = 1.0;
		}

	}

	Color Color::operator+(const Color& SecondColor) const {
		Color newColor;
		newColor.red = SecondColor.red + red;
		newColor.blue = SecondColor.blue + blue;
		newColor.green = SecondColor.green + green;
		newColor.alpha = SecondColor.alpha + alpha;
		newColor.Clamp();
		return newColor;
	}

	Color Color::operator-(const Color& SecondColor) const {
		Color newColor;
		newColor.red = red - SecondColor.red;
		newColor.blue = blue - SecondColor.blue;
		newColor.green = green - SecondColor.green;
		newColor.alpha = alpha - SecondColor.alpha;
		newColor.Clamp();
		return newColor;
	}

	Color Color::operator*(const float& num) const {
		Color newColor;
		newColor.red = red * num;
		newColor.blue = blue * num;
		newColor.green = green * num;
		newColor.alpha = alpha * num;
		newColor.Clamp();
		return newColor;
	}