#include "StdAfx.h"
#include "Cube.h"


Cube::Cube(void):
	FourDimensionalObject(8, 18, 5)
{
	float length1 = 100.0f;
	float length2 = 100.0f;
	float length3 = 100.0f;
	float normalY = 1.0f;
	mRadius = Vector4f(length1/2, length2/2, 0, length3/2).length();
	for (int i = -1; i <= 1; i+=2)
		for (int j = -1; j <= 1; j+=2)
			for (int k = -1; k <= 1; k+=2)
				AddVertex(Vector4f(i * length1/2, j * length2/2, 0, k * length3/2));

	AddCube(00, 01, 02, 03, 04, 05, 06, 07, 
		Vector4f(0.0, 0.0, normalY/std::fabs(normalY), 0.0));
}

Cube::Cube(const Vector4f &center, 
		float length1, float length2, float length3,
		float normalY) :
	FourDimensionalObject(8, 18, 5),
	mCenter(center)
{
	assert(normalY != 0);
	mRadius = Vector4f(length1/2, length2/2, 0, length3/2).length();
	for (int i = -1; i <= 1; i+=2)
		for (int j = -1; j <= 1; j+=2)
			for (int k = -1; k <= 1; k+=2)
				AddVertex(center + Vector4f(i * length1/2, j * length2/2, 0, k * length3/2));

	AddCube(00, 01, 02, 03, 04, 05, 06, 07, 
		Vector4f(0.0, 0.0, normalY/std::fabs(normalY), 0.0));
}

Cube::Cube(const Vector4f &vertex1, 
		const Vector4f &edge1, const Vector4f &edge2, const Vector4f &edge3,
		const Vector4f &normal):
	FourDimensionalObject(8, 18, 5)
{
	assert(false);
}

Cube::~Cube(void)
{
}

std::auto_ptr<ThreeDimensionalObject> Cube::Slice(const HyperPlane &plane) const
{
	if (plane.Distance(mCenter) > mRadius)
		return std::auto_ptr<ThreeDimensionalObject>(nullptr);
	return FourDimensionalObject::Slice(plane);
}

void Cube::AddCube(size_t v0, size_t v1, size_t v2, size_t v3, 
		           size_t v4, size_t v5, size_t v6, size_t v7,
				   const Vector4f &normal)
{
	AddTetrahedron(v0, v1, v3, v5, normal);
	AddTetrahedron(v0, v2, v3, v6, normal);
	AddTetrahedron(v0, v4, v5, v6, normal);
	AddTetrahedron(v3, v5, v6, v7, normal);
	AddTetrahedron(v0, v3, v5, v6, normal);
}
