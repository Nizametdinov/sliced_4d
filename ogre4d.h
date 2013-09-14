#ifndef __TutorialApplication_h_
#define __TutorialApplication_h_

#include "BaseApplication.h"
#include "HyperCube.h"
#include "FixedXYHyperPlane.h"
#include "FourDimensionalScene.h"

class Ogre4dApplication : public BaseApplication
{
public:
    Ogre4dApplication(void);
    virtual ~Ogre4dApplication(void);

protected:
    virtual void createScene(void);

	 // Ogre::FrameListener
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

    // OIS::KeyListener
    virtual bool keyPressed( const OIS::KeyEvent &arg );
    virtual bool keyReleased( const OIS::KeyEvent &arg );
    // OIS::MouseListener
    virtual bool mouseMoved( const OIS::MouseEvent &arg );
    virtual bool mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id );
    virtual bool mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id );

	virtual Ogre::StringVector getDetailsPanelFields();
	virtual void updateDetailsPanelContent();
private:
	void renderSlice();
	void clearSlice();

	void MakeFloor();
	void MakeWall();

	bool mRotatePlane;
	float mAngle;

	int mShiftPlane;
	int mGoingForward;
	int mGoingRight;
	int mGoingUp;
	bool mFastMove;

	float mShiftPlaneSpeed;
	float mTopSpeed;
	Ogre::Vector3 mVelocity;

	Ogre::SceneNode *mCameraYawNode;

	Vector4f mCameraPosition;

	FixedXYHyperPlane mCameraPlane;
	FourDimensionalScene m4dScene;
	std::vector<Ogre::SceneNode *> mNodes;
	std::vector<Ogre::ManualObject *> mManualObjects;
	std::vector<Ogre::String> mMaterials;

	OgreBites::ParamsPanel* m4dDetailsPanel;
};

#endif // #ifndef __TutorialApplication_h_