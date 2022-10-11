#include "Triangle.h"

Triangle2D::Triangle2D()
{
	v1 = Vector2(0.0, 0.0);
	v2 = Vector2(0.0, 0.0);
	v3 = Vector2(0.0, 0.0);

	c1 = Black;
	c2 = Black;
	c3 = Black;
}

Triangle2D::Triangle2D(Vector2 a1, Vector2 a2, Vector2 a3, Color b1, Color b2, Color b3)
{
	v1 = a1;
	v2 = a2;
	v3 = a3;

	c1 = b1;
	c2 = b2;
	c3 = b3;
}

bool Triangle2D::inside(int x, int y) 
{
	Vector2 P(x, y);

	Vector2 edgeP0 = (v2 - v1).perpendicular();
	Vector2 g0 = P - v1;
	float result0 = edgeP0.dot(g0);

	Vector2 edgpeP1 = (v3 - v2).perpendicular();
	Vector2 g1 = P - v2;
	float result1 = edgpeP1.dot(g1);

	Vector2 edgeP2 = (v1 - v3).perpendicular();
	Vector2 g2 = P - v3;
	float result2 = edgeP2.dot(g2);

	if (result0 >= 0 && result1 >= 0 && result2 >= 0) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

Triangle2D::Triangle2D(Triangle3D triangle)
{
	v1 = Vector2(triangle.v1.x, triangle.v1.y);
	v2 = Vector2(triangle.v2.x, triangle.v2.y);
	v3 = Vector2(triangle.v3.x, triangle.v3.y);

	c1 = triangle.c1;
	c2 = triangle.c2;
	c3 = triangle.c3;
}

void Triangle2D::calculateBarycentricCoordinates(Vector2 P, float& lambda1, float& lambda2, float& lambda3)
{
	float area = determinant(v2 - v3, v1 - v3);

	lambda1 = roundf((determinant(v2 - v3, P - v3) / area)* 10000) / 10000; 
	lambda2 = roundf((determinant(P - v3, v1 - v3) / area) * 10000) / 10000;
	lambda3 = roundf((1.0 - lambda1 - lambda2) * 10000) / 10000;
}

Triangle3D::Triangle3D()
{
	v1 = Vector4(0.0, 0.0, 0.0, 1.0);
	v2 = Vector4(0.0, 0.0, 0.0, 1.0);
	v3 = Vector4(0.0, 0.0, 0.0, 1.0);

	c1 = White;
	c2 = White;
	c3 = White;

	shouldDraw = true;
}

Triangle3D::Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3, Color pC1, Color pC2, Color pC3)
{
	v1 = pV1;
	v2 = pV2;
	v3 = pV3;

	c1 = pC1;
	c2 = pC2;
	c3 = pC3;
}

void Triangle3D::transform(Matrix4 matrix)
{
	v1 = matrix * v1;
	v2 = matrix * v2;
	v3 = matrix * v3;
}