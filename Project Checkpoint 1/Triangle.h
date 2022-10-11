#ifndef Triangle_H
#define Triangle_H
#include <cmath>
#include "Color.h"
#include "Vector.h"
#include "Matrix.h"

struct Triangle3D;

struct Triangle2D {

	Vector2 v1;
	Vector2 v2;
	Vector2 v3;

	Color c1;
	Color c2;
	Color c3;

public:
	Triangle2D();
	Triangle2D(Vector2 a1, Vector2 a2, Vector2 a3, Color b1, Color b2, Color b3);
	Triangle2D(Triangle3D triangle);
	bool inside(int x, int y);


	void calculateBarycentricCoordinates(Vector2 P, float& lambda1, float& lambda2, float& lambda3);
};

struct Triangle3D {
	
	Vector4 v1;
	Vector4 v2;
	Vector4 v3;

	Color c1;
	Color c2;
	Color c3;

	bool shouldDraw;

public:
	Triangle3D();
	Triangle3D(Vector4 pV1, Vector4 pV2, Vector4 pV3, Color pC1, Color pC2, Color pC3);
	void transform(Matrix4 matrix);
};

#endif