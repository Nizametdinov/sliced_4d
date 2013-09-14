//#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#include "stdafx.h"
//#endif

#include "ogre4d.h"

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    int APIENTRY _tWinMain(HINSTANCE hInstance,
						   HINSTANCE hPrevInstance,
						   LPTSTR    lpCmdLine,
						   int       nCmdShow)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Ogre4dApplication app;
 
        try 
        {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBoxA( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR| MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " << e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif
