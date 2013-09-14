#include "StdAfx.h"

#include "../HyperCube.h"
#include "../FixedXYHyperPlane.h"
//#define BOOST_TEST_MODULE HyperCube
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(HyperCube_Tests)
{
	Vector4f center(0.0, 0.0, 0.0, 0.0);
	HyperCube hc(center, 10.0, 10.0, 10.0, 10.0);
	FixedXYHyperPlane hp;
	hp.Shift(5.0);

	std::vector<Ogre::Vector3> vertices;
	for (int i = -1; i <= 1; i += 2)
		for (int j = -1; j <= 1; j += 2)
			for (int k = -1; k <= 1; k += 2)
				vertices.push_back(Ogre::Vector3(i * 5.0f, j * 5.0f, k * 5.0f));

	std::auto_ptr<ThreeDimensionalObject> slice(hc.Slice(hp));
	ThreeDimensionalObject::ConstVertexIterator it = slice->VerticesConstBegin();
	for (; it != slice->VerticesConstEnd(); ++it)
		if (std::find(vertices.begin(), vertices.end(), *it) == vertices.end())
			BOOST_ERROR("Slice contain unexpected vertex: " << *it);
}
