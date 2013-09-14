#include "StdAfx.h"

#include "../Vector4f.h"
//#define BOOST_TEST_MODULE Vector4f
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(Vector4f_tests)
{
	Vector4f v;
	Vector4f v1(0.1f, -0.1f, 0.5f, 1e-5f);
	Vector4f v2(v1);
	Vector4f v3(0.0f, 0.0f, 0.0f, 0.0f);
	v = v1;
	BOOST_CHECK_EQUAL(v1[3], 1e-5f);
	BOOST_CHECK(v == v1);
	BOOST_CHECK(v1 == v2);
	BOOST_CHECK(v1 != v3);

	Vector4f v4(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4f v5(1.0f, 2.0f, 3.0f, 4.0f);
	Vector4f v6(2.0f, 3.0f, 4.0f, 5.0f);
	Vector4f v7 = v4;

	// Length
	BOOST_CHECK_EQUAL(v4.length(), 2.0f);
	BOOST_CHECK_EQUAL(v4.squaredLength(), 4.0f);
	v7.normalise();
	BOOST_CHECK(v7 == Vector4f(0.5f, 0.5f, 0.5f, 0.5f));
	BOOST_CHECK_EQUAL((-v6).normMaxAbs(), 5.0f);

	// Arithmetical operations
	BOOST_CHECK(v1 - v2 == v3);
	BOOST_CHECK(v4 + v5 == v6);
	BOOST_CHECK(2.0f * v5 == Vector4f(2.0f, 4.0f, 6.0f, 8.0f));
	BOOST_CHECK(v5 * 2.0f == Vector4f(2.0f, 4.0f, 6.0f, 8.0f));
	BOOST_CHECK(v5 / 2.0f == Vector4f(0.5f, 1.0f, 1.5f, 2.0f));

	float scalar_product = v4 * v5;
	BOOST_CHECK_EQUAL(scalar_product, 10.0f);
	v3 += v4;
	v2 -= v1;
	v4 *= 2.0f;
	v5 /= 2.0f;
	BOOST_CHECK(v3 == Vector4f(1.0f, 1.0f, 1.0f, 1.0f));
	BOOST_CHECK(v2 == Vector4f());
	BOOST_CHECK(v4 == Vector4f(2.0f, 2.0f, 2.0f, 2.0f));
	BOOST_CHECK(v5 == Vector4f(0.5f, 1.0f, 1.5f, 2.0f));
	BOOST_CHECK(-v3 == Vector4f(-1.0f, -1.0f, -1.0f, -1.0f));
}
