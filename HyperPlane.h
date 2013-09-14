#ifndef __HyperPlane_h_
#define __HyperPlane_h_

#include "Vector4f.h"
#include <OgreVector3.h>

class HyperPlane
{
public:
	HyperPlane(float A, float B, float C, float D, float E);
	HyperPlane(const Vector4f &normal, float rho);
	~HyperPlane(void);

	float Distance(const Vector4f &point) const;
	float Value(const Vector4f &point) const;

	const Vector4f &Normal() const
	{ return mNormal; }

	enum IntersectionType
	{
		IST_NONE,
		IST_POINT, // Inner point of segment
		IST_VERTEX,
		IST_LINE
	};

	IntersectionType Intersection(
		const Vector4f &point1, const Vector4f &point2, 
		Vector4f &result_point) const;

	// TODO: Replace by pure virtual functions
	virtual Ogre::Vector3 GetInnerCoordinates(const Vector4f &point) const
	{ return Ogre::Vector3(); }
	virtual Vector4f GetGlobalCoordinates(const Ogre::Vector3 &innerPoint) const
	{ return Vector4f(); }
protected:
	Vector4f mNormal;
	float mRho;
};

#endif //__HyperPlane_h_
