#include "StdAfx.h"
#include "HyperCube.h"
#include "HyperPlane.h"

#include <vector>
#include <iostream>

HyperCube::HyperCube(void) :
	FourDimensionalObject(16, 50, 40), mCenter(0.0f, 0.0f, 0.0f, 0.0f)
{
	float a = 100.0f;
	float b = 100.0f;
	float c = 100.0f;
	float d = 100.0f;
	mRadius = Vector4f(a/2, b/2, c/2, d/2).length();
	for (int i = -1; i <= 1; i+=2)
		for (int j = -1; j <= 1; j+=2)
			for (int k = -1; k <= 1; k+=2)
				for (int l = -1; l <= 1; l+=2)
					AddVertex(Vector4f(i * a/2, j * b/2, k * c/2, l * d/2));
	AddCube(00, 01, 02, 03, 04, 05, 06, 07, Vector4f(-1.0, 0.0, 0.0, 0.0));
	AddCube(010, 011, 012, 013, 014, 015, 016, 017, Vector4f(1.0, 0.0, 0.0, 0.0));
	AddCube(00, 01, 02, 03, 010, 011, 012, 013, Vector4f(0.0, -1.0, 0.0, 0.0));
	AddCube(04, 05, 06, 07, 014, 015, 016, 017, Vector4f(0.0,  1.0, 0.0, 0.0));
	AddCube(00, 01, 04, 05, 010, 011, 014, 015, Vector4f(0.0, 0.0, -1.0, 0.0));
	AddCube(02, 03, 06, 07, 012, 013, 016, 017, Vector4f(0.0, 0.0,  1.0, 0.0));
	AddCube(00, 02, 04, 06, 010, 012, 014, 016, Vector4f(0.0, 0.0, 0.0, -1.0));
	AddCube(01, 03, 05, 07, 011, 013, 015, 017, Vector4f(0.0, 0.0, 0.0,  1.0));
}

HyperCube::HyperCube(const Vector4f &center, float a, float b, float c, float d) :
	FourDimensionalObject(16, 50, 40), mCenter(center)
{
	assert(a > 0 && b > 0 && c > 0 && d > 0);
	mRadius = Vector4f(a/2, b/2, c/2, d/2).length();
	for (int i = -1; i <= 1; i+=2)
		for (int j = -1; j <= 1; j+=2)
			for (int k = -1; k <= 1; k+=2)
				for (int l = -1; l <= 1; l+=2)
					AddVertex(center + Vector4f(i * a/2, j * b/2, k * c/2, l * d/2));
	AddCube(00, 01, 02, 03, 04, 05, 06, 07, Vector4f(-1.0, 0.0, 0.0, 0.0));
	AddCube(010, 011, 012, 013, 014, 015, 016, 017, Vector4f(1.0, 0.0, 0.0, 0.0));
	AddCube(00, 01, 02, 03, 010, 011, 012, 013, Vector4f(0.0, -1.0, 0.0, 0.0));
	AddCube(04, 05, 06, 07, 014, 015, 016, 017, Vector4f(0.0,  1.0, 0.0, 0.0));
	AddCube(00, 01, 04, 05, 010, 011, 014, 015, Vector4f(0.0, 0.0, -1.0, 0.0));
	AddCube(02, 03, 06, 07, 012, 013, 016, 017, Vector4f(0.0, 0.0,  1.0, 0.0));
	AddCube(00, 02, 04, 06, 010, 012, 014, 016, Vector4f(0.0, 0.0, 0.0, -1.0));
	AddCube(01, 03, 05, 07, 011, 013, 015, 017, Vector4f(0.0, 0.0, 0.0,  1.0));
}

HyperCube::~HyperCube(void)
{
}

void HyperCube::AddCube(size_t v0, size_t v1, size_t v2, size_t v3, 
		                size_t v4, size_t v5, size_t v6, size_t v7,
				        const Vector4f &normal)
{
	AddTetrahedron(v0, v1, v3, v5, normal);
	AddTetrahedron(v0, v2, v3, v6, normal);
	AddTetrahedron(v0, v4, v5, v6, normal);
	AddTetrahedron(v3, v5, v6, v7, normal);
	AddTetrahedron(v0, v3, v5, v6, normal);
}

const size_t HyperCube::edges[32][2] = 
{
	{0, 1},	{1, 2},	{2, 3},	{3, 0}, // Верхний квадрат \ 
	{0, 4}, {1, 5},	{2, 6},	{3, 7}, // Боковые ребра    | Верхний куб
	{4, 5},	{5, 6},	{6, 7},	{7, 4}, // Нижний квадрат  / 
	{8, 9}, {9, 10}, {10, 11}, {11, 8},     // Верхний квадрат \ 
	{8, 12}, {9, 13}, {10, 14}, {11, 15},   // Боковые ребра    | Нижний куб
	{12, 13}, {13, 14}, {14, 15}, {15, 12}, // Нижний квадрат  / 
	{0, 8}, // 24
	{1, 9}, 
	{2, 10},
	{3, 11},
	{4, 12}, // 28
	{5, 13},
	{6, 14},
	{7, 15}
};

const size_t HyperCube::faces[24][4] = 
{
	{0, 1,  2,  3},
	{0, 4,  8,  5},
	{1, 5,  9,  6},
	{2, 6, 10,  7},
	{3, 7, 11,  4},
	{8, 9, 10, 11}, // Верхний куб

	{12, 13, 14, 15},
	{12, 16, 20, 17},
	{13, 17, 21, 18},
	{14, 18, 22, 19},
	{15, 19, 23, 16},
	{20, 21, 22, 23}, // Нижний куб

	{ 0, 24, 12, 25},
	{ 1, 25, 13, 26},
	{ 2, 26, 14, 27},
	{ 3, 27, 15, 24}, // 15
	{ 4, 24, 16, 28},
	{ 5, 25, 17, 29},
	{ 6, 26, 18, 30},
	{ 7, 27, 19, 31}, // 19
	{ 8, 28, 20, 29},
	{ 9, 29, 21, 30},
	{10, 30, 22, 31},
	{11, 31, 23, 28}
};

const size_t HyperCube::cubes[8][6] = 
{
	{0,  1,  2,  3,  4, 5},
	{0, 12, 13, 14, 15, 6},
	{1, 12, 17, 20, 16, 7},
	{2, 13, 18, 21, 17, 8},
	{3, 14, 19, 22, 18, 9},
	{4, 15, 16, 23, 19, 10},
	{5, 20, 21, 22, 23, 11},
	{6,  7,  8,  9, 10, 11}
};

std::auto_ptr<ThreeDimensionalObject> HyperCube::Slice(const HyperPlane &plane) const
{
	if (plane.Distance(mCenter) > mRadius)
		return std::auto_ptr<ThreeDimensionalObject>(nullptr);
	return FourDimensionalObject::Slice(plane);
}
