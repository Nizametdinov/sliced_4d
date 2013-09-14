// ogre4d.cpp : Defines the entry point for the application.
//

//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "stdafx.h"
//#endif

#include "ogre4d.h"
#include <limits>

Ogre4dApplication::Ogre4dApplication(void) :
	mRotatePlane(false),
	mAngle(0),
	mShiftPlane(0),
	mShiftPlaneSpeed(10),
	mGoingForward(0),
	mGoingRight(0),
	mGoingUp(0),
	mTopSpeed(10),
	mFastMove(false),
	mVelocity(Ogre::Vector3::ZERO)
{
}
 
Ogre4dApplication::~Ogre4dApplication(void)
{
}

//-------------------------------------------------------------------------------------
void Ogre4dApplication::createScene(void)
{
	mCameraPosition = Vector4f(0, 0, 60, 0);
	mCameraYawNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	mCamera->setPosition(0, 0, 0);
	mCameraYawNode->attachObject(mCamera);
	mCameraYawNode->setPosition(0, 60, 0);

    // Set ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.9f, 0.9f, 0.9f));
 
    // Create a light
    //Ogre::Light* l = mSceneMgr->createLight("MainLight");
    //l->setPosition(20,80,50);

	Ogre::ResourceGroupManager::getSingleton().createResourceGroup("solid colour materials");

	Ogre::MaterialManager &materialMgr = Ogre::MaterialManager::getSingleton();

	Ogre::MaterialPtr material1 = materialMgr.create("solid black", "solid colour materials");
	Ogre::Pass *pass1 = material1->getTechnique(0)->getPass(0);
	pass1->setDiffuse(Ogre::ColourValue(0.0f, 0.0f, 0.0f));
	pass1->setAmbient(Ogre::ColourValue(0.1f, 0.1f, 0.1f));

	material1 = materialMgr.create("solid white", "solid colour materials");
	pass1 = material1->getTechnique(0)->getPass(0);
	pass1->setDiffuse(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	pass1->setAmbient(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	material1 = materialMgr.create("solid gray", "solid colour materials");
	pass1 = material1->getTechnique(0)->getPass(0);
	pass1->setDiffuse(Ogre::ColourValue(0.5f, 0.5f, 0.5f));
	pass1->setAmbient(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	material1 = materialMgr.create("solid red", "solid colour materials");
	pass1 = material1->getTechnique(0)->getPass(0);
	pass1->setDiffuse(Ogre::ColourValue(1.0f, 0.0f, 0.0f));
	pass1->setAmbient(Ogre::ColourValue(1.0f, 0.0f, 0.0f));

	material1 = materialMgr.create("solid blue", "solid colour materials");
	pass1 = material1->getTechnique(0)->getPass(0);
	pass1->setDiffuse(Ogre::ColourValue(0.0f, 0.0f, 1.0f));
	pass1->setAmbient(Ogre::ColourValue(0.0f, 0.0f, 1.0f));

	material1 = materialMgr.create("solid green", "solid colour materials");
	pass1 = material1->getTechnique(0)->getPass(0);
	pass1->setDiffuse(Ogre::ColourValue(0.0f, 1.0f, 0.0f));
	pass1->setAmbient(Ogre::ColourValue(0.0f, 1.0f, 0.0f));

	material1 = materialMgr.create("solid yellow", "solid colour materials");
	pass1 = material1->getTechnique(0)->getPass(0);
	pass1->setDiffuse(Ogre::ColourValue(1.0f, 1.0f, 0.0f));
	pass1->setAmbient(Ogre::ColourValue(1.0f, 1.0f, 0.0f));

	MakeFloor();
	MakeWall();

	m4dScene.AddHyperCube(Vector4f(0, 0, 25, 0), 50, 50, 50, 50);
	m4dScene.AddHyperCube(Vector4f(60, 0, 25, 0), 50, 50, 50, 50);
	m4dScene.AddHyperCube(Vector4f(0, 60, 25, 0), 50, 50, 50, 50);
	m4dScene.AddHyperCube(Vector4f(0, 0, 25, 60), 50, 50, 50, 50);

	for (int i = 0; i < 4; i++)
		mNodes.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode());
	for (int i = 0; i < 4; i++)
		mManualObjects.push_back(nullptr);

	mMaterials.push_back("solid red");
	mMaterials.push_back("solid blue");
	mMaterials.push_back("solid green");
	mMaterials.push_back("solid yellow");

	mAngle = 0.1f;
	mRotatePlane = false;
	
	renderSlice();
}

Ogre::ManualObject *render3dObject(
	ThreeDimensionalObject *obj3d, const Ogre::String &name, const Ogre::String &materialName)
{
	if (obj3d == nullptr || obj3d->IsEmpty())
		return nullptr;
	Ogre::ManualObject* obj = new Ogre::ManualObject(name);
	obj->estimateVertexCount(obj3d->GetVerticesCount());
	obj->estimateIndexCount(obj3d->GetTrianglesCount() * 3 * 2);

	obj->begin(materialName);

	ThreeDimensionalObject::ConstVertexIterator it = obj3d->VerticesConstBegin();
	for (; it != obj3d->VerticesConstEnd(); ++it)
		obj->position(*it);

	ThreeDimensionalObject::ConstTriangleIterator tri = obj3d->TrianglesConstBegin();
	for (; tri != obj3d->TrianglesConstEnd(); ++tri)
	{
		obj->triangle(tri->vertices[0], tri->vertices[1], tri->vertices[2]);
		obj->triangle(tri->vertices[0], tri->vertices[2], tri->vertices[1]);
	}

	obj->end();
	return obj;
}
 
void Ogre4dApplication::renderSlice()
{
	static unsigned long int num = 0;
	m4dScene.MakeSlice(mCameraPlane);
	FourDimensionalScene::SliceIterator sit = m4dScene.SliceConstBegin();
	for (int i = 0; sit != m4dScene.SliceConstEnd(); ++sit, ++i)
	{
		mManualObjects[i] = render3dObject(*sit, Ogre::StringConverter::toString(num), mMaterials[i]);
		if (mManualObjects[i] != nullptr)
			mNodes[i]->attachObject(mManualObjects[i]);
	}
}

void Ogre4dApplication::clearSlice()
{
	for (size_t i = 0; i < mManualObjects.size(); ++i)
	{
		if (mManualObjects[i] != nullptr)
		{
			mNodes[i]->detachObject(mManualObjects[i]);
			mSceneMgr->destroyManualObject(mManualObjects[i]);
			mManualObjects[i] = nullptr;
		}
	}
}

void Ogre4dApplication::MakeFloor()
{
	float cubeSize = 400;
	bool white = true;
	for (int i = -2; i < 2; i++)
	{
		for (int j = -2; j < 2; j++)
		{
			for (int k = -2; k < 2; k++)
			{
				Vector4f center((i + 0.5) * cubeSize, (j + 0.5) * cubeSize, 0.0f, (k + 0.5) * cubeSize);
				m4dScene.AddCube(center, cubeSize, cubeSize, cubeSize, 1.0f);
				mNodes.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode());
				mManualObjects.push_back(nullptr);
				mMaterials.push_back(white ? "solid white" : "solid black");
				white = !white;
			}
			white = !white;
		}
		white = !white;
	}
}

void Ogre4dApplication::MakeWall()
{
	float height = 100;
	float width = 10;
	float floorSize = 1600;

	for (size_t coord = 0; coord < 3; coord++)
		for (int i = -1; i <= 1; i+=2)
		{
			Vector4f center(0.0f, 0.0f, 0.0f, 0.5*height);
			center[coord] = i*0.5*(floorSize+width);
			std::swap(center[2], center[3]);

			Vector4f size(floorSize, floorSize, floorSize, height);
			size[coord] = width;
			std::swap(size[2], size[3]);

			m4dScene.AddHyperCube(center, size[0], size[1], size[2], size[3]);
			mNodes.push_back(mSceneMgr->getRootSceneNode()->createChildSceneNode());
			mManualObjects.push_back(nullptr);
			mMaterials.push_back("solid gray");
		}
}

bool Ogre4dApplication::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	bool ret = BaseApplication::frameRenderingQueued(evt);
	if (!ret)
		return false;

	bool updateSlice = false;
	if (mAngle != 0.0f)
	{
		mCameraPosition = mCameraPlane.GetGlobalCoordinates(mCameraYawNode->getPosition());
		mCameraPlane.RotateAroundXY(mAngle, mCameraPosition);
		mCameraYawNode->setPosition(mCameraPlane.GetInnerCoordinates(mCameraPosition));
		updateSlice = true;
		mAngle = 0.0f;
	}

	if (mShiftPlane != 0)
	{
		updateSlice = true;
		float shift = (mFastMove ? 20 : 1) * mShiftPlane * mShiftPlaneSpeed * evt.timeSinceLastFrame;
		mCameraPlane.Shift(shift);
	}

	if (updateSlice)
	{
		clearSlice();
		renderSlice();
	}

	{
		// build our acceleration vector based on keyboard input composite
		Ogre::Vector3 accel = Ogre::Vector3::ZERO;
		accel.z -= mGoingForward;
		accel.x += mGoingRight;
		accel.y += mGoingUp;
		//accel += mGoingForward * mCamera->getDirection();
		//accel += mGoingRight * mCamera->getRight();
		//accel += mGoingUp * mCamera->getUp();

		// if accelerating, try to reach top speed in a certain time
		Ogre::Real topSpeed = mFastMove ? mTopSpeed * 20 : mTopSpeed;
		if (accel.squaredLength() != 0)
		{
			accel.normalise();
			mVelocity += accel * topSpeed * evt.timeSinceLastFrame * 10;
		}
		// if not accelerating, try to stop in a certain time
		else mVelocity -= mVelocity * evt.timeSinceLastFrame * 10;

		Ogre::Real tooSmall = std::numeric_limits<Ogre::Real>::epsilon();

		// keep camera velocity below top speed and above epsilon
		if (mVelocity.squaredLength() > topSpeed * topSpeed)
		{
			mVelocity.normalise();
			mVelocity *= topSpeed;
		}
		else if (mVelocity.squaredLength() < tooSmall * tooSmall)
			mVelocity = Ogre::Vector3::ZERO;

		if (mVelocity != Ogre::Vector3::ZERO) 
			//mCamera->move(mVelocity * evt.timeSinceLastFrame);
			mCameraYawNode->translate(mVelocity, Ogre::Node::TS_LOCAL);
	}

	mCameraPosition = mCameraPlane.GetGlobalCoordinates(mCameraYawNode->getPosition());

	return true;
}

bool Ogre4dApplication::keyPressed( const OIS::KeyEvent &arg )
{
	switch (arg.key) 
	{
	case OIS::KC_Q:
		mShiftPlane = -1;
		return true;
	case OIS::KC_E:
		mShiftPlane = 1;
		return true;
	case OIS::KC_S:
	case OIS::KC_DOWN:
		mGoingForward = -1;
		return true;
	case OIS::KC_W:
	case OIS::KC_UP:
		mGoingForward = 1;
		return true;
	case OIS::KC_A:
	case OIS::KC_LEFT:
		mGoingRight = -1;
		return true;
	case OIS::KC_D:
	case OIS::KC_RIGHT:
		mGoingRight = 1;
		return true;
	case OIS::KC_PGUP:
		mGoingUp = 1;
		return true;
	case OIS::KC_PGDOWN:
		mGoingUp = -1;
		return true;
	case OIS::KC_LSHIFT:
		mFastMove = true;
		return true;
	default:
		break;
	}
	return BaseApplication::keyPressed(arg);
}

bool Ogre4dApplication::keyReleased( const OIS::KeyEvent &arg )
{
	switch (arg.key) 
	{
	case OIS::KC_Q:
		mShiftPlane = 0;
		return true;
	case OIS::KC_E:
		mShiftPlane = 0;
		return true;
	case OIS::KC_S:
	case OIS::KC_DOWN:
	case OIS::KC_W:
	case OIS::KC_UP:
		mGoingForward = 0;
		return true;
	case OIS::KC_A:
	case OIS::KC_LEFT:
	case OIS::KC_D:
	case OIS::KC_RIGHT:
		mGoingRight = 0;
		return true;
	case OIS::KC_PGUP:
	case OIS::KC_PGDOWN:
		mGoingUp = 0;
		return true;
	case OIS::KC_LSHIFT:
		mFastMove = false;
		return true;
	default:
		break;
	}
	
	return BaseApplication::keyReleased(arg);
}

bool Ogre4dApplication::mouseMoved( const OIS::MouseEvent &arg )
{
	if (mRotatePlane)
	{
		mAngle = Ogre::Degree(-arg.state.X.rel * 0.15f).valueRadians();
		return true;
	}

	mCameraYawNode->yaw(Ogre::Degree(-arg.state.X.rel * 0.15f), Ogre::Node::TS_LOCAL);
	mCamera->pitch(Ogre::Degree(-arg.state.Y.rel * 0.15f));

	{
		// Angle of rotation around the X-axis.
		float pitchAngle = 2 * Ogre::Degree(Ogre::Math::ACos(mCamera->getOrientation().w)).valueDegrees();
 
		// Just to determine the sign of the angle we pick up above, the
		// value itself does not interest us.
		float pitchAngleSign = mCamera->getOrientation().x;
 
		// Limit the pitch between -90 degress and +90 degrees, Quake3-style.
		if (pitchAngle > 90.0f)
		{
			if (pitchAngleSign > 0)
				// Set orientation to 90 degrees on X-axis.
				mCamera->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
														 Ogre::Math::Sqrt(0.5f), 0, 0));
			else if (pitchAngleSign < 0)
				// Sets orientation to -90 degrees on X-axis.
				mCamera->setOrientation(Ogre::Quaternion(Ogre::Math::Sqrt(0.5f),
                                                         -Ogre::Math::Sqrt(0.5f), 0, 0));
		}

	}
		
	return BaseApplication::mouseMoved(arg);
}

bool Ogre4dApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (id == OIS::MB_Left)
	{
		mRotatePlane = true;
		return true;
	}
	return BaseApplication::mousePressed(arg, id);
}

bool Ogre4dApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
	if (id == OIS::MB_Left)
	{
		mRotatePlane = false;
		return true;
	}
	return BaseApplication::mouseReleased(arg, id);
}

Ogre::StringVector Ogre4dApplication::getDetailsPanelFields()
{
	Ogre::StringVector items;
	items.push_back("cam.pW");
    items.push_back("cam.pX");
    items.push_back("cam.pY");
    items.push_back("cam.pZ");
    items.push_back("");
    items.push_back("cam.oW");
    items.push_back("cam.oX");
    items.push_back("cam.oY");
    items.push_back("cam.oZ");
    items.push_back("");
    items.push_back("Filtering");
    items.push_back("Poly Mode");

	return items;
}

void Ogre4dApplication::updateDetailsPanelContent()
{
    mDetailsPanel->setParamValue(0, Ogre::StringConverter::toString(mCameraPosition[0]));
    mDetailsPanel->setParamValue(1, Ogre::StringConverter::toString(mCameraPosition[1]));
    mDetailsPanel->setParamValue(2, Ogre::StringConverter::toString(mCameraPosition[2]));
	mDetailsPanel->setParamValue(3, Ogre::StringConverter::toString(mCameraPosition[3]));
    mDetailsPanel->setParamValue(5, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().w));
    mDetailsPanel->setParamValue(6, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().x));
    mDetailsPanel->setParamValue(7, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().y));
    mDetailsPanel->setParamValue(8, Ogre::StringConverter::toString(mCamera->getDerivedOrientation().z));

	Ogre::String filtering;
	switch (mFiltering)
    {
    case Ogre::TFO_BILINEAR:
        filtering = "Bilinear";
        break;
    case Ogre::TFO_TRILINEAR:
        filtering = "Trilinear";
        break;
    case Ogre::TFO_ANISOTROPIC:
        filtering = "Anisotropic";
        break;
    default:
        filtering = "None";
    }
	mDetailsPanel->setParamValue(10, filtering);

	Ogre::String polyMode;
	switch (mCamera->getPolygonMode())
    {
    case Ogre::PM_SOLID:
        polyMode = "Solid";
        break;
    case Ogre::PM_WIREFRAME:
        polyMode = "Wireframe";
        break;
    default:
        polyMode = "Points";
    }
	mDetailsPanel->setParamValue(11, polyMode);
}
