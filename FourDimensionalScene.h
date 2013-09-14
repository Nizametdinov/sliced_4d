#ifndef __FourDimensionalScene_h_
#define __FourDimensionalScene_h_

#include "Vector4f.h"
#include "ThreeDimensionalObject.h"
#include "HyperPlane.h"

class FourDimensionalObject;

class FourDimensionalScene
{
public:
	FourDimensionalScene(void);
	~FourDimensionalScene(void);

	void AddCube(const Vector4f &center, 
		float lengthW, float lengthX, float lengthZ, float normalY);
	void AddHyperCube(const Vector4f &center, 
		float lengthW, float lengthX, float lengthY, float lengthZ);

	void MakeSlice(const HyperPlane &hp);

	typedef std::vector<ThreeDimensionalObject *> Slice;
	typedef Slice::const_iterator SliceIterator;

	SliceIterator SliceConstBegin() const
	{ return mSlice.cbegin(); }
	SliceIterator SliceConstEnd() const
	{ return mSlice.cend(); }
private:
	void ClearSlice();

	std::vector<FourDimensionalObject *> mObjects;
	Slice mSlice;
};

#endif