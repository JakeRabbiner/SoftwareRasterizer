#ifndef Vector_H
#define Vector_H
#include <cmath>
#include <iostream>

struct Vector2
{
	float x;
	float y;

	Vector2();
	Vector2(float a, float b);
	Vector2 operator*(float b);
	Vector2 operator+(Vector2 x);
	Vector2 operator-(Vector2 x);
	float magnitude();
	float dot(Vector2 temp);
	Vector2 normalize();
	Vector2 perpendicular();
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;

	Vector4();
	Vector4(float pX, float pY, float pZ, float pW);
	Vector4 operator*(float a);
	Vector4 operator+(Vector4 x);
	Vector4 operator-(Vector4 x);

	double magnitude();
	void normalize();
	double dot(Vector4 temp);
	Vector4 cross(Vector4 temp);
};

float determinant(Vector2 a, Vector2 b);

#endif
