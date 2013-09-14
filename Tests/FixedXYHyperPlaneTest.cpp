#include "StdAfx.h"

#include "../FixedXYHyperPlane.h"
//#define BOOST_TEST_MODULE HyperPlane
#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_CASE(FixedXYHyperPlane_Tests)
{
	FixedXYHyperPlane hp;
	Vector4f zero(0.0f, 0.0f, 0.0f, 0.0f);
	Vector4f v1(1.0f, 1.0f, 1.0f, 0.0f);
	BOOST_CHECK_EQUAL(hp.Distance(zero), 0.0f);
	BOOST_CHECK(hp.Normal() == Vector4f(1.0f, 0.0f, 0.0f, 0.0f));

	hp.Shift(5.0f);
	BOOST_CHECK_EQUAL(hp.Value(zero), -5.0f);
	hp.Shift(-5.0f);

	hp.RotateAroundXY(2.0 * std::atan(1.0), zero);
	Vector4f eps = hp.Normal() - Vector4f(0.0f, 0.0f, 0.0f, 1.0f);
	BOOST_CHECK(eps.normMaxAbs() < 1e-7);

	Ogre::Vector3 coord = hp.GetInnerCoordinates(v1);
	BOOST_CHECK(coord == Ogre::Vector3(1.0, 1.0, -1.0));

	// Над поведением функции RotateAroundXY еще нужно подумать:
	// нужно ли сохранять внутренние координаты fixedPoint после поворота?
	hp.RotateAroundXY(2.0 * std::atan(1.0), v1);
	BOOST_CHECK(std::abs(hp.GetInnerCoordinates(v1)[2]) < 1e-7);
	std::cout << hp.GetInnerCoordinates(v1) << std::endl;
}