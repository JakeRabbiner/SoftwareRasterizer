#include "Matrix.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

Matrix4::Matrix4()
{
	ix = 1.0;
	jx = 0.0;
	kx = 0.0;
	ox = 0.0;
	iy = 0.0;
	jy = 1.0;
	ky = 0.0;
	oy = 0.0;
	iz = 0.0;
	jz = 0.0;
	kz = 1.0;
	oz = 0.0;
	iw = 0.0;
	jw = 0.0;
	kw = 0.0;
	ow = 1.0;
}

Matrix4::Matrix4(float pIX, float pJX, float pKX, float pOX, float pIY, float pJY, float pKY, float pOY, float pIZ, float pJZ, float pKZ, float pOZ, float pIW, float pJW, float pKW, float pOW)
{
	ix = pIX;
	jx = pJX;
	kx = pKX;
	ox = pOX;
	iy = pIY;
	jy = pJY;
	ky = pKY;
	oy = pOY;
	iz = pIZ;
	jz = pJZ;
	kz = pKZ;
	oz = pOZ;
	iw = pIW;
	jw = pJW;
	kw = pKW;
	ow = pOW;
}

Vector4 Matrix4::operator*(Vector4 vector)
{
	Vector4 v;
	v.x = ix * vector.x + jx * vector.y + kx * vector.z + ox * vector.w;
	v.y = iy * vector.x + jy * vector.y + ky * vector.z + oy * vector.w;
	v.z = iz * vector.x + jz * vector.y + kz * vector.z + oz * vector.w;
	v.w = iw * vector.x + jw * vector.y + kw * vector.z + ow * vector.w;

	return v;
}

Matrix4 Matrix4::operator*(Matrix4 matrix)
{
	Matrix4 m;

	m.ix = ix * matrix.ix + jx * matrix.iy + kx * matrix.iz + ox * matrix.iw;
	m.jx = ix * matrix.jx + jx * matrix.jy + kx * matrix.jz + ox * matrix.jw;
	m.kx = ix * matrix.kx + jx * matrix.ky + kx * matrix.kz + ox * matrix.kw;
	m.ox = ix * matrix.ox + jx * matrix.oy + kx * matrix.oz + ox * matrix.ow;

	m.iy = iy * matrix.ix + jy * matrix.iy + ky * matrix.iz + oy * matrix.iw;
	m.jy = iy * matrix.jx + jy * matrix.jy + ky * matrix.jz + oy * matrix.jw;
	m.ky = iy * matrix.kx + jy * matrix.ky + ky * matrix.kz + oy * matrix.kw;
	m.oy = iy * matrix.ox + jy * matrix.oy + ky * matrix.oz + oy * matrix.ow;

	m.iz = iz * matrix.ix + jz * matrix.iy + kz * matrix.iz + oz * matrix.iw;
	m.jz = iz * matrix.jx + jz * matrix.jy + kz * matrix.jz + oz * matrix.jw;
	m.kz = iz * matrix.kx + jz * matrix.ky + kz * matrix.kz + oz * matrix.kw;
	m.oz = iz * matrix.ox + jz * matrix.oy + kz * matrix.oz + oz * matrix.ow;

	m.iw = iw * matrix.ix + jw * matrix.iy + kw * matrix.iz + ow * matrix.iw;
	m.jw = iw * matrix.jx + jw * matrix.jy + kw * matrix.jz + ow * matrix.jw;
	m.kw = iw * matrix.kx + jw * matrix.ky + kw * matrix.kz + ow * matrix.kw;
	m.ow = iw * matrix.ox + jw * matrix.oy + kw * matrix.oz + ow * matrix.ow;

	return m;
}

void Matrix4::print()
{
	std::cout << ix << ", " << jx << ", " << kx << ", " << ox << std::endl;
	std::cout << iy << ", " << jy << ", " << ky << ", " << oy << std::endl;
	std::cout << iz << ", " << jz << ", " << kz << ", " << oz << std::endl;
	std::cout << iw << ", " << jw << ", " << kw << ", " << ow << std::endl;
}

// Standalone Transformation Functions 

Matrix4 Translate3D(float tX, float tY, float tZ)
{
	Matrix4 m;
	m.ox = tX;
	m.oy = tY;
	m.oz = tZ;
	return m;
}

Matrix4 Scale3D(float sX, float sY, float sZ)
{
	Matrix4 m;
	m.ix = sX;
	m.jy = sY;
	m.kz = sZ;
	return m;
}

Matrix4 RotateX3D(float degrees)
{
	float cosF = cos(degrees* M_PI / 180.0);
	float sinF = sin(degrees * M_PI / 180.0);
	Matrix4 m(1, 0, 0, 0, 0, cosF, sinF, 0, 0, -sinF, cosF, 0, 0, 0, 0, 1);
	return m;
}

Matrix4 RotateY3D(float degrees)
{

	float cosF = cos(degrees* M_PI / 180.0);
	float sinF = sin(degrees * M_PI / 180.0);
	Matrix4 m(cosF, 0, -sinF, 0, 0, 1, 0, 0, sinF, 0, cosF, 0, 0, 0, 0, 1);
	return m;
}

Matrix4 RotateZ3D(float degrees)
{

	float cosF = cos(degrees * M_PI / 180.0);
	float sinF = sin(degrees * M_PI / 180.0);
	Matrix4 m(cosF, sinF, 0, 0, -sinF, cosF, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	return m;
}

Matrix4 Rotate3D(float degreesX, float degreesY, float degreesZ)
{
	return RotateX3D(degreesX) * RotateY3D(degreesY) * RotateZ3D(degreesZ);
}

Matrix4 Rotate3D(float degrees, Vector4 vec)
{
	float alpha = atanf(vec.x / vec.z);
	float beta = acosf(vec.y / vec.magnitude());
	float alphaRadians = alpha * M_PI / 180.0;
	float betaRadians = beta * M_PI / 180.0;
	return RotateY3D(-alphaRadians) * RotateX3D(-betaRadians) * RotateY3D(degrees * M_PI / 180.0) * RotateX3D(betaRadians) * RotateY3D(alphaRadians);
}

Matrix4 LookAt(Vector4 eye, Vector4 spot, Vector4 up)
{
	Matrix4 temp;
	Vector4 look = (spot - eye);
	look.normalize();
	Vector4 right = look.cross(up);
	right.normalize();
	up = right.cross(look);
	up.normalize();

	temp.ix = right.x;
	temp.jx = right.y;
	temp.kx = right.z;
	temp.iy = up.x;
	temp.jy = up.y;
	temp.ky = up.z;
	temp.iz = -look.x;
	temp.jz = -look.y;
	temp.kz = -look.z;
	Matrix4 viewMatrix = temp * Translate3D(-eye.x, -eye.y, -eye.z);
	return viewMatrix;
}

Matrix4 Orthographic(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	float tx = -((minX + maxX) / 2);
	float ty = -((minY + maxY) / 2);
	float tz = -((minZ + maxZ) / 2);

	float sx = 2 / (maxX - minX);
	float sy = 2 / (maxY - minY);
	float sz = 2 / (maxZ - minZ);

	return Scale3D(sx, sy, sz) * Translate3D(tx, ty, tz);
}

Matrix4 Perspective(float fovY, float aspect, float nearZ, float farZ)
{
	Matrix4 p;
	float ymaxPZ = tanf((fovY / 2) * M_PI / 180.0);
	float F = 1 / ymaxPZ;
	p.ix = F / aspect;
	p.jy = F;
	p.kz = (farZ + nearZ) / (nearZ - farZ);
	p.kw = -1;
	p.oz = (2 * nearZ * farZ) / (nearZ - farZ);
	p.ow = 0;
	return p;
}

Matrix4 Viewport(float x, float y, float width, float height)
{
	return Translate3D(x, y, 0) * Scale3D(width, height, 1) * Scale3D(0.5, 0.5, 0.5) * Translate3D(1.0, 1.0, -1.0);
}