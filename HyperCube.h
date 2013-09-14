#ifndef __HyperCube_h_
#define __HyperCube_h_

#include "Vector4f.h"
#include "FourDimensionalObject.h"

class HyperCube: 
	public FourDimensionalObject
{
public:
	HyperCube(void);
	HyperCube(const Vector4f &center, 
		float lengthW, float lengthX, float lengthY, float lengthZ);
	~HyperCube(void);
	virtual std::auto_ptr<ThreeDimensionalObject> Slice(const HyperPlane &plane) const;
private:
	Vector4f mCenter;
	float mRadius;
	void AddCube(size_t v0, size_t v1, size_t v2, size_t v3, 
		         size_t v4, size_t v5, size_t v6, size_t v7,
				 const Vector4f &normal);
	static const size_t edges[32][2];
	static const size_t faces[24][4];
	static const size_t cubes[8][6];
};

#endif //__HyperCube_h__

