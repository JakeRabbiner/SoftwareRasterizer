#include "Vector.h"

Vector2::Vector2()
{
	x = 0.0;
	y = 0.0;
}

Vector2::Vector2(float a, float b) 
{
	x = a;
	y = b;
}

Vector2 Vector2::operator*(float b)
{
	Vector2 temp;
	temp.x = x * b;
	temp.y = y * b;
	return temp;
}

Vector2 Vector2::operator+(Vector2 b)
{
	Vector2 temp;
	temp.x = x + b.x;
	temp.y = y + b.y;
	return temp;
}

Vector2 Vector2::operator-(Vector2 b)
{
	Vector2 temp;
	temp.x = x - b.x;
	temp.y = y - b.y;
	return temp;
}

float Vector2::magnitude()
{
	return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

float Vector2::dot(Vector2 temp)
{
	return x * temp.x + y * temp.y;
}

Vector2 Vector2::normalize()
{
	Vector2 newVector2;
	float DENOM = magnitude();
	newVector2.x = (1 / DENOM) * x; 
	newVector2.y = (1 / DENOM) * y; 
	return newVector2; 
}

Vector2 Vector2::perpendicular()
{
	return Vector2(-y, x);
}

float determinant(Vector2 a, Vector2 b)
{
	return (b.x * a.y) - (b.y * a.x);
}

//Vector4 Section

Vector4::Vector4() 
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 0.0;
}

Vector4::Vector4(float pX, float pY, float pZ, float pW)
{
	x = pX;
	y = pY;
	z = pZ;
	w = pW;
}

Vector4 Vector4::operator*(float b)
{
	Vector4 temp;
	temp.x = x * b;
	temp.y = y * b;
	temp.z = z * b;
	temp.w = w * b;
	return temp;
}

Vector4 Vector4::operator+(Vector4 b)
{
	Vector4 temp;
	temp.x = x + b.x;
	temp.y = y + b.y;
	temp.z = z + b.z;
	temp.w = w + b.w;
	return temp;
}

Vector4 Vector4::operator-(Vector4 b)
{
	Vector4 temp;
	temp.x = x - b.x;
	temp.y = y - b.y;
	temp.z = z - b.z;
	temp.w = w - b.w;
	return temp;
}

double Vector4::magnitude()
{
	return sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0) + pow(w, 2.0));
}

void Vector4::normalize()
{
	float factor = magnitude();
	x = (1 / factor) * x;
	y = (1 / factor) * y;
	z = (1 / factor) * z;
	w = (1 / factor) * w;
}

double Vector4::dot(Vector4 temp)
{
	return x * temp.x + y * temp.y + z * temp.z + w * temp.w;
}

Vector4 Vector4::cross(Vector4 temp)
{
	Vector4 myVec;
	myVec.x = y * temp.z - z * temp.y;
	myVec.y = z * temp.x - x * temp.z;
	myVec.z = x * temp.y - y * temp.x;
	return myVec;
}