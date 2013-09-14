#ifndef __Cube_h_
#define __Cube_h_

#include "FourDimensionalObject.h"

class Cube :
	public FourDimensionalObject
{
public:
	Cube(void);
	Cube(const Vector4f &center, 
		float length1, float length2, float length3,
		float normalY);
	Cube(const Vector4f &vertex1, 
		const Vector4f &edge1, const Vector4f &edge2, const Vector4f &edge3,
		const Vector4f &normal);
	~Cube(void);

	virtual std::auto_ptr<ThreeDimensionalObject> Slice(const HyperPlane &plane) const;
private:
	Vector4f mCenter;
	float mRadius;

	void AddCube(size_t v0, size_t v1, size_t v2, size_t v3, 
		         size_t v4, size_t v5, size_t v6, size_t v7,
				 const Vector4f &normal);
};

#endif //__Cube_h_