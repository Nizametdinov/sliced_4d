#include "StdAfx.h"
#include "FourDimensionalObject.h"

namespace
{
	struct Intersection
	{
		HyperPlane::IntersectionType type;
		size_t v1;
		size_t v2;
	};
	struct TetrahedronSlice
	{
		TetrahedronSlice(): vertices_count(0) {}
		size_t vertices[4];
		size_t vertices_count;
		void AddVertex(size_t id)
		{
			if (vertices_count == 4)
				return;
			for (size_t i = 0; i < vertices_count; i++)
				if (vertices[i] == id)
					return;
			vertices[vertices_count] = id;
			vertices_count++;
		}
	};
	// Номера ребер из которых состоят грани тетраэдра
	size_t triangles[4][3] = {
		{0, 3, 1},
		{1, 4, 2},
		{2, 5, 0},
		{3, 4, 5}
	};
}

FourDimensionalObject::FourDimensionalObject(void)
{
}

FourDimensionalObject::FourDimensionalObject(
		size_t verticesCount, size_t edgesCount, size_t tetrahedronsCount)
{
	vertices.reserve(verticesCount);
	edges.reserve(edgesCount);
	tetrahedrons.reserve(tetrahedronsCount);
}

FourDimensionalObject::~FourDimensionalObject(void)
{
}

bool FourDimensionalObject::Edge::operator == (const Edge &other)
{
	bool result = vertices[0] == other.vertices[0] && vertices[1] == other.vertices[1];
	result |= vertices[1] == other.vertices[0] && vertices[0] == other.vertices[1];
	return result;
}

bool FourDimensionalObject::Tetrahedron::operator == (const Tetrahedron &other)
{
	bool result = vertices[0] == other.vertices[0] || vertices[0] == other.vertices[1]
		|| vertices[0] == other.vertices[2] || vertices[0] == other.vertices[3];
	result &= vertices[1] == other.vertices[0] || vertices[1] == other.vertices[1]
		|| vertices[1] == other.vertices[2] || vertices[1] == other.vertices[3];
	result &= vertices[2] == other.vertices[0] || vertices[2] == other.vertices[1]
		|| vertices[2] == other.vertices[2] || vertices[2] == other.vertices[3];
	result &= vertices[3] == other.vertices[0] || vertices[3] == other.vertices[1]
		|| vertices[3] == other.vertices[2] || vertices[3] == other.vertices[3];
	return result;
}

template<class RandomAccessTetrahedronsIterator, class RandomAccessVerticesIterator>
ThreeDimensionalObject Slice(const HyperPlane &hp,
	RandomAccessTetrahedronsIterator tet_begin,
	RandomAccessTetrahedronsIterator tet_end,
	RandomAccessVerticesIterator vert_begin,
	RandomAccessVerticesIterator vert_end)
{
}

std::auto_ptr<ThreeDimensionalObject> FourDimensionalObject::Slice(const HyperPlane &hp) const
{
	std::vector<Intersection> intersections(edges.size());
	Vector4f tmp;
	std::auto_ptr<ThreeDimensionalObject> result(new ThreeDimensionalObject());
	
	for (size_t i = 0; i < edges.size(); i++)
	{
		intersections[i].type = hp.Intersection(
			vertices[edges[i].vertices[0]],
			vertices[edges[i].vertices[1]],
			tmp);
		if (intersections[i].type == HyperPlane::IST_LINE)
		{
			intersections[i].v1 = result->AddVertex(
				hp.GetInnerCoordinates(vertices[edges[i].vertices[0]]));
			intersections[i].v2 = result->AddVertex(
				hp.GetInnerCoordinates(vertices[edges[i].vertices[1]]));
		} 
		else if (intersections[i].type != HyperPlane::IST_NONE)
		{
			intersections[i].v1 = result->AddVertex(
				hp.GetInnerCoordinates(tmp));
		}
	}

	std::vector<Tetrahedron>::const_iterator it = tetrahedrons.cbegin();
	for (; it != tetrahedrons.cend(); ++it)
	{
		int lines = 0;
		int none = 0;
		for (int i = 0; i < 6; i++)
		{
			if (intersections[it->edges[i]].type == HyperPlane::IST_LINE)
				lines++;
			else if (intersections[it->edges[i]].type == HyperPlane::IST_NONE)
				none++;
		}

		if (none == 6)
			continue;

		TetrahedronSlice tri;
		if (lines == 6)
		{
			for (int i = 0; i < 4; i++) // Triangles
			{
				tri.vertices_count = 0;
				for (int j = 0; j < 3; j++) // Edges
				{
					tri.AddVertex(intersections[it->edges[triangles[i][j]]].v1);
					tri.AddVertex(intersections[it->edges[triangles[i][j]]].v2);
				}
				result->AddTriangle(tri.vertices[0], tri.vertices[1], tri.vertices[2]);
			}
			continue;
		}
		for (int i = 0; i < 6; i++)
		{
			if (intersections[it->edges[i]].type == HyperPlane::IST_LINE)
			{
				tri.AddVertex(intersections[it->edges[i]].v1);
				tri.AddVertex(intersections[it->edges[i]].v2);
			}
			else if (intersections[it->edges[i]].type != HyperPlane::IST_NONE)
				tri.AddVertex(intersections[it->edges[i]].v1);
		}
		if (tri.vertices_count == 3)
			result->AddTriangle(tri.vertices[0], tri.vertices[1], tri.vertices[2]);
		else if (tri.vertices_count == 4)
			result->AddQuadrangle(tri.vertices[0], tri.vertices[1], tri.vertices[2], tri.vertices[3]);
	}

	return result;
}

size_t FourDimensionalObject::AddVertex(const Vector4f &vertex)
{
	for (size_t i = 0; i < vertices.size(); ++i)
		if (vertices[i] == vertex)
			return i;
	vertices.push_back(vertex);
	return vertices.size() - 1;
}

size_t FourDimensionalObject::AddTetrahedron(
	size_t v1, size_t v2, size_t v3, size_t v4, const Vector4f &normal)
{
	Tetrahedron tetrahedron;
	tetrahedron.vertices[0] = v1;
	tetrahedron.vertices[1] = v2;
	tetrahedron.vertices[2] = v3;
	tetrahedron.vertices[3] = v4;
	// Первые три ребра отходят о вершины 0 к вершинам 1, 2 и 3
	// Остальные ребра 1->2, 2->3, 3->1
	for (size_t i = 0; i < tetrahedrons.size(); ++i)
		if (tetrahedrons[i] == tetrahedron)
			return i;
	tetrahedron.edges[0] = AddEdge(v1, v2);
	tetrahedron.edges[1] = AddEdge(v1, v3);
	tetrahedron.edges[2] = AddEdge(v1, v4);
	tetrahedron.edges[3] = AddEdge(v2, v3);
	tetrahedron.edges[4] = AddEdge(v3, v4);
	tetrahedron.edges[5] = AddEdge(v4, v2);
	tetrahedron.normal = normal;
	tetrahedrons.push_back(tetrahedron);
	return tetrahedrons.size() - 1;
}

size_t FourDimensionalObject::AddEdge(size_t v1, size_t v2)
{
	Edge edge;
	edge.vertices[0] = v1;
	edge.vertices[1] = v2;
	for (size_t i = 0; i < edges.size(); ++i)
		if (edges[i] == edge)
			return i;
	edges.push_back(edge);
	return edges.size() - 1;
}
