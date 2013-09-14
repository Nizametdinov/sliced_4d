#include "StdAfx.h"

#include "../HyperPlane.h"
//#define BOOST_TEST_MODULE HyperPlane
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(HyperPlane_Tests)
{
	HyperPlane hp1(1.0f, 0, 0, 0, 0);
	HyperPlane hp2(1.0f, 2.0f, -2.0f, 4.0f, 5.0f);
	Vector4f zero(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4f v1(1.0f, 1.0f, 1.0f, 1.0f);
	BOOST_CHECK_EQUAL(hp1.Distance(zero), 0.0f);
	BOOST_CHECK_EQUAL(hp2.Distance(zero), 1.0f);
	BOOST_CHECK_EQUAL(hp1.Distance(-v1), 1.0f);
	BOOST_CHECK_EQUAL(hp2.Distance(v1), 2.0f);
	BOOST_CHECK_EQUAL(hp1.Value(zero), 0.0f);
	BOOST_CHECK_EQUAL(hp2.Value(zero), 1.0f);
	BOOST_CHECK_EQUAL(hp1.Value(-v1), -1.0f);
	BOOST_CHECK_EQUAL(hp2.Value(v1), 2.0f);
}

BOOST_AUTO_TEST_CASE(HyperPlane_IntersectionTests)
{
	HyperPlane hp1(1.0f, 0, 0, 1.0f, 0);
	Vector4f v1(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4f v2(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4f v3(1.0f, 0.0f, 0.0f, -1.0f);
	Vector4f result;

	HyperPlane::IntersectionType inters = hp1.Intersection(v1, v2, result);
	BOOST_CHECK(inters == HyperPlane::IST_VERTEX);
	BOOST_CHECK(result == v1);

	inters = hp1.Intersection(v2, v2, result);
	BOOST_CHECK(inters == HyperPlane::IST_NONE);

	inters = hp1.Intersection(v2, -2*v2, result);
	BOOST_CHECK(inters == HyperPlane::IST_POINT);
	BOOST_CHECK(result == v1);

	inters = hp1.Intersection(v1, v3, result);
	BOOST_CHECK(inters == HyperPlane::IST_LINE);

	HyperPlane hp2(0.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	Vector4f v4(1.0f, 0.5f, 0.5f, 0.0f);
	inters = hp2.Intersection(v2, v3, result);
	BOOST_CHECK(inters == HyperPlane::IST_POINT);
	BOOST_CHECK(result == v4);
}
