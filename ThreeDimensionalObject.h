#ifndef __ThreeDimensionalObject_h_
#define __ThreeDimensionalObject_h_

#include <vector>
#include "OgreVector3.h"

class ThreeDimensionalObject
{
public:
	ThreeDimensionalObject(void);
	~ThreeDimensionalObject(void);

	bool IsEmpty() const;

	size_t AddVertex(float x, float y, float z);
	size_t AddVertex(const Ogre::Vector3 v);
	size_t AddTriangle(size_t vert1, size_t vert2, size_t vert3);
	void AddQuadrangle(size_t vert1, size_t vert2, size_t vert3, size_t vert4);

	struct Triangle
	{
		Triangle(size_t v1, size_t v2, size_t v3)
		{
			vertices[0] = v1;
			vertices[1] = v2;
			vertices[2] = v3;
		}
		size_t vertices[3];
		void FlipNormal();
		bool operator ==(const Triangle &other);
	};

	typedef std::vector<Ogre::Vector3> VertexArray;
	typedef VertexArray::const_iterator ConstVertexIterator;

	typedef std::vector<Triangle> TriangleArray;
	typedef TriangleArray::const_iterator ConstTriangleIterator;

	size_t GetVerticesCount() const
	{ return mVertices.size(); }
	ConstVertexIterator VerticesConstBegin() const
	{ return mVertices.cbegin(); }
	ConstVertexIterator VerticesConstEnd() const
	{ return mVertices.cend(); }

	size_t GetTrianglesCount() const
	{ return mTriangles.size(); }
	ConstTriangleIterator TrianglesConstBegin() const
	{ return mTriangles.cbegin(); }
	ConstTriangleIterator TrianglesConstEnd() const
	{ return mTriangles.cend(); }
private:
	VertexArray mVertices;
	TriangleArray mTriangles;
};

#endif //__ThreeDimensionalObject_h_