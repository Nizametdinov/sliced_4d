#include "StdAfx.h"
#include "ThreeDimensionalObject.h"

ThreeDimensionalObject::ThreeDimensionalObject(void)
{
}


ThreeDimensionalObject::~ThreeDimensionalObject(void)
{
}

bool ThreeDimensionalObject::IsEmpty() const
{
	return mTriangles.empty();
}

size_t ThreeDimensionalObject::AddVertex(float x, float y, float z)
{
	Ogre::Vector3 vertex(x, y, z);
	return AddVertex(vertex);
}

size_t ThreeDimensionalObject::AddVertex(const Ogre::Vector3 vertex)
{
	for (size_t i = 0; i < mVertices.size(); ++i)
		if (mVertices[i] == vertex)
			return i;
	mVertices.push_back(vertex);
	return mVertices.size() - 1;
}

size_t ThreeDimensionalObject::AddTriangle(size_t vert1, size_t vert2, size_t vert3)
{
	assert(vert1 != vert2 && vert1 != vert3 && vert2 != vert3);
	Triangle triangle(vert1, vert2, vert3);
	for (size_t i = 0; i < mTriangles.size(); ++i)
		if (mTriangles[i] == triangle)
			return i;
	mTriangles.push_back(triangle);
	return mTriangles.size() - 1;
}

void ThreeDimensionalObject::AddQuadrangle(size_t vert1, size_t vert2, size_t vert3, size_t vert4)
{
	Ogre::Vector3 v1 = mVertices[vert2] - mVertices[vert1];
	Ogre::Vector3 v2 = mVertices[vert3] - mVertices[vert1];
	Ogre::Vector3 v3 = mVertices[vert4] - mVertices[vert1];
	float cos1 = v1.dotProduct(v2) / v1.length() / v2.length();
	float cos2 = v1.dotProduct(v3) / v1.length() / v3.length();

	if (cos1 < cos2)
		std::swap(vert3, vert4);

	AddTriangle(vert1, vert2, vert4);
	AddTriangle(vert2, vert3, vert4);
}

bool ThreeDimensionalObject::Triangle::operator ==(const ThreeDimensionalObject::Triangle &other)
{
	bool result = vertices[0] == other.vertices[0] || vertices[0] == other.vertices[1]
		|| vertices[0] == other.vertices[2];
	result &= vertices[1] == other.vertices[0] || vertices[1] == other.vertices[1]
		|| vertices[1] == other.vertices[2];
	result &= vertices[2] == other.vertices[0] || vertices[2] == other.vertices[1]
		|| vertices[2] == other.vertices[2];
	return result;
}

void ThreeDimensionalObject::Triangle::FlipNormal()
{
	std::swap(vertices[1], vertices[2]);
}
