#include "StdAfx.h"
#include "Vector4f.h"


Vector4f::Vector4f(void)
{
	mValue[0] = 0.0f;
	mValue[1] = 0.0f;
	mValue[2] = 0.0f;
	mValue[3] = 0.0f;
}

Vector4f::Vector4f(float w, float x, float y, float z)
{
	mValue[0] = w;
	mValue[1] = x;
	mValue[2] = y;
	mValue[3] = z;
}

Vector4f::Vector4f(const Vector4f &v)
{
	for (int i = 0; i < 4; i++)
		mValue[i] = v.mValue[i];
}

Vector4f::~Vector4f(void)
{
}

float Vector4f::length() const
{
	float result = 0.0f;
	for (int i = 0; i < 4; i++)
		result += mValue[i] * mValue[i];
	return std::sqrtf(result);
}

float Vector4f::squaredLength() const
{
	float result = 0.0f;
	for (int i = 0; i < 4; i++)
		result += mValue[i] * mValue[i];
	return result;
}

void Vector4f::normalise()
{
	float norm = length();
	if (norm == 0.0f)
		return;
	for (int i = 0; i < 4; i++)
		mValue[i] /= norm;
}

float Vector4f::normMaxAbs() const
{
	float norm = 0.0f;
	for (int i = 0; i < 4; i++)
		norm = max(std::fabsf(mValue[i]), norm);
	return norm;
}

Vector4f& Vector4f::operator = (const Vector4f &v) 
{
	for (int i = 0; i < 4; i++)
		mValue[i] = v.mValue[i];
	return *this;
}

float Vector4f::operator [] (size_t i) const 
{
	assert(i < 4);
	return mValue[i];
}

float& Vector4f::operator [] (size_t i) 
{
	assert(i < 4);
	return mValue[i];
}

bool Vector4f::operator == (const Vector4f &v) const 
{
	bool result = true;
	for (int i = 0; i < 4 && result; i++)
		result &= mValue[i] == v.mValue[i];
	return result;
}

Vector4f& Vector4f::operator *= (float a) 
{
	for (int i = 0; i < 4; i++)
		mValue[i] *= a;
	return *this;
}

Vector4f& Vector4f::operator /= (float a) 
{
	for (int i = 0; i < 4; i++)
		mValue[i] /= a;
	return *this;
}

Vector4f& Vector4f::operator += (const Vector4f &v)
{
	for (int i = 0; i < 4; i++)
		mValue[i] += v.mValue[i];
	return *this;
}

Vector4f& Vector4f::operator -= (const Vector4f &v)
{
	for (int i = 0; i < 4; i++)
		mValue[i] -= v.mValue[i];
	return *this;
}

Vector4f Vector4f::operator * (float a) const 
{
	Vector4f result;
	for (int i = 0; i < 4; i++)
		result.mValue[i] = a * mValue[i];
	return result;
}

Vector4f Vector4f::operator / (float a) const 
{
	Vector4f result;
	for (int i = 0; i < 4; i++)
		result.mValue[i] = mValue[i] / a;
	return result;
}

Vector4f Vector4f::operator + (const Vector4f &v) const 
{
	Vector4f result;
	for (int i = 0; i < 4; i++)
		result.mValue[i] = mValue[i] + v.mValue[i];
	return result;
}

Vector4f Vector4f::operator - (const Vector4f &v) const 
{
	Vector4f result;
	for (int i = 0; i < 4; i++)
		result.mValue[i] = mValue[i] - v.mValue[i];
	return result;
}

Vector4f Vector4f::operator - () const
{
	return Vector4f(-mValue[0], -mValue[1], -mValue[2], -mValue[3]);
}

float Vector4f::operator * (const Vector4f &v) const
{
	float result = 0.0f;
	for (int i = 0; i < 4; i++)
		result += mValue[i] * v.mValue[i];
	return result;
}

Vector4f operator * (float a, const Vector4f &v)
{
	Vector4f result;
	for (int i = 0; i < 4; i++)
		result.mValue[i] = a * v.mValue[i];
	return result;
}
