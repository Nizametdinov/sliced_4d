#include "StdAfx.h"
#include "HyperPlane.h"

HyperPlane::HyperPlane(float A, float B, float C, float D, float E) :
	mNormal(A, B, C, D)
{
	float norm = mNormal.length();
	assert(norm != 0.);
	mRho = E / norm;
	mNormal.normalise();
}

HyperPlane::HyperPlane(const Vector4f &normal, float rho) :
	mNormal(normal)
{
	float norm = mNormal.length();
	assert(norm != 0.);
	mRho = rho / norm;
	mNormal.normalise();
}

HyperPlane::~HyperPlane(void)
{
}

float HyperPlane::Distance(const Vector4f &point) const
{
	return std::fabsf(mNormal * point + mRho);
}

float HyperPlane::Value(const Vector4f &point) const
{
	return mNormal * point + mRho;
}

// Нахождение точки пересечения отрезка и гиперплоскости
HyperPlane::IntersectionType HyperPlane::Intersection(
		const Vector4f &point1, const Vector4f &point2, 
		Vector4f &result_point) const
{
	float v1 = Value(point1);
	float v2 = Value(point2);

	if (v1 == 0.0 && v2 == 0.0)
		return IST_LINE;
	if (v1 * v2 > 0.0)
		return IST_NONE;
	if (v1 == 0.0)
	{
		result_point = point1;
		return IST_VERTEX;
	}
	if (v2 == 0.0)
	{
		result_point = point2;
		return IST_VERTEX;
	}

	result_point = point2 * (v1 / (v1 - v2)) - point1 * (v2 / (v1 - v2));
	return IST_POINT;
}
