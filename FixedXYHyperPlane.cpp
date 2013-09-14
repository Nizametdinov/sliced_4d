#include "StdAfx.h"
#include "FixedXYHyperPlane.h"

FixedXYHyperPlane::FixedXYHyperPlane(void):
	HyperPlane(1.0f, 0.0f, 0.0f, 0.0f, 0.0f)
{
}


FixedXYHyperPlane::~FixedXYHyperPlane(void)
{
}

void FixedXYHyperPlane::RotateAroundXY(float angle, const Vector4f &fixedPoint)
{
	float tmp = Value(fixedPoint);
	float normal0 = mNormal[0] * std::cos(angle) - mNormal[3] * std::sin(angle);
	mNormal[3]    = mNormal[0] * std::sin(angle) + mNormal[3] * std::cos(angle);
	mNormal[0] = normal0;
	mRho = -mNormal * fixedPoint + tmp;
}

void FixedXYHyperPlane::Shift(float shift)
{
	mRho -= shift;
}

Ogre::Vector3 FixedXYHyperPlane::GetInnerCoordinates(const Vector4f &point) const
{
	float cos_a = mNormal[0];
	float sin_a = mNormal[3];
	//    w =  cos_a * point[0] + sin_a * point[3]
	float z = -sin_a * point[0] + cos_a * point[3];
	Ogre::Vector3 result(point[1], point[2], z);
	return result;
}

Vector4f FixedXYHyperPlane::GetGlobalCoordinates(const Ogre::Vector3 &innerPoint) const
{
	// Когда плоскость повернута так, что нормаль равна {1, 0, 0, 0}
	// уравнение плоскости принимает вид w = -mRho.
	// Берем за координату точки {-mRho, innerPoint} и применяем поворот,
	// переводящий {1, 0, 0, 0} в mNormal
	float cos_a = mNormal[0];
	float sin_a = mNormal[3];
	float w = cos_a * (-mRho) - sin_a * innerPoint[2];
	float z = sin_a * (-mRho) + cos_a * innerPoint[2];
	Vector4f result(w, innerPoint[0], innerPoint[1], z);
	return result;
}
