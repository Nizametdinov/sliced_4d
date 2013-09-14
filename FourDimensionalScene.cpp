#include "StdAfx.h"
#include "FourDimensionalScene.h"
#include "HyperCube.h"
#include "Cube.h"

FourDimensionalScene::FourDimensionalScene(void)
{
}


FourDimensionalScene::~FourDimensionalScene(void)
{
	std::vector<FourDimensionalObject *>::const_iterator it = mObjects.cbegin();
	for (; it != mObjects.cend(); ++it)
		delete *it;
	SliceIterator sit = mSlice.cbegin();
	for (; sit != mSlice.cend(); ++sit)
		if (*sit != nullptr)
			delete *sit;
}

void FourDimensionalScene::AddHyperCube(const Vector4f &center, float a, float b, float c, float d)
{
	mObjects.push_back(new HyperCube(center, a, b, c, d));
}

void FourDimensionalScene::AddCube(const Vector4f &center, 
		float lengthW, float lengthX, float lengthZ, float normalY)
{
	mObjects.push_back(new Cube(center, lengthW, lengthX, lengthZ, normalY));
}

void FourDimensionalScene::MakeSlice(const HyperPlane &hp)
{
	ClearSlice();
	std::vector<FourDimensionalObject *>::const_iterator it = mObjects.cbegin();
	for (; it != mObjects.cend(); ++it)
		mSlice.push_back((*it)->Slice(hp).release());
}

void FourDimensionalScene::ClearSlice()
{
	SliceIterator sit = mSlice.cbegin();
	for (; sit != mSlice.cend(); ++sit)
		if (*sit != nullptr)
			delete *sit;
	mSlice.clear();
}
