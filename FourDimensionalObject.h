#ifndef __FourDimensionalObject_h_
#define __FourDimensionalObject_h_

#include "HyperPlane.h"
#include "ThreeDimensionalObject.h"
#include "Vector4f.h"
#include <vector>
#include <memory>

class FourDimensionalObject
{
public:
	FourDimensionalObject(void);
	~FourDimensionalObject(void);

	virtual std::auto_ptr<ThreeDimensionalObject> Slice(const HyperPlane &) const;
protected:
	FourDimensionalObject(
		size_t verticesCount, size_t edgesCount, size_t tetrahedronsCount);

	size_t AddVertex(const Vector4f &);
	size_t AddTetrahedron(
		size_t v1, size_t v2, size_t v3, size_t v4, const Vector4f &normal);

private:
	struct Edge
	{
		size_t vertices[2];
		bool operator == (const Edge &);
	};

	struct Tetrahedron
	{
		size_t vertices[4];
		size_t edges[6]; // Первые три ребра отходят о вершины 0 к вершинам 1, 2 и 3
		// Остальные ребра 1->2, 2->3, 3->1
		Vector4f normal;
		bool operator == (const Tetrahedron &);
	};

	// TODO: rename members
	std::vector<Vector4f> vertices;
	std::vector<Edge> edges;
	std::vector<Tetrahedron> tetrahedrons;

	size_t AddEdge(size_t, size_t);
};

#endif //__FourDimensionalObject_h_