#ifndef Matrix_H
#define Matrix_H
#include <iostream>
#include <math.h>
#include <cmath>
#include "Vector.h"


struct Matrix4 {

	float ix;
	float jx;
	float kx;
	float ox;
	float iy;
	float jy;
	float ky;
	float oy;
	float iz;
	float jz;
	float kz;
	float oz;
	float iw;
	float jw;
	float kw;
	float ow;

	Matrix4();
	Matrix4(float pIX, float pJX, float pKX, float pOX, float pIY, float pJY, float pKY, float pOY, float pIZ, float pJZ, float pKZ, float pOZ, float pIW, float pJW, float pKW, float pOW);
	Vector4 operator*(Vector4 vector);
	Matrix4 operator*(Matrix4 matrix);
	void print();

};

//Standalone

Matrix4 Translate3D(float tX, float tY, float tZ);
Matrix4 Scale3D(float sX, float sY, float sZ);
Matrix4 RotateX3D(float degrees);
Matrix4 RotateY3D(float degrees);
Matrix4 RotateZ3D(float degrees);
Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ);
Matrix4 Rotate3D(float degrees, Vector4 vec);

Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up);

Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ);
Matrix4 Viewport(float x, float y, float width, float height);

#endif