#if !defined(OPERATING_SYSTEM_HEADER)
#define OPERATING_SYTEM_HEADER


#if defined(VK_USE_PLATFORM_WIN32_KHR)

#include <windows.h>

#elif defined(VK_USE_PLATEFORM_XCB_KHR)
#include <xcb/xcb.h>
#include <dlfcn.h>
#include <cstdlib>

#elif defined(VK_USE_PLATFORM_XLIB_KHR)

#include <x11/Xlib.h>
#include <x11/xutil.h>
#include <dlfcn.h>
#include <cstdlib>

#endif // 

#include <cstring>
#include <iostream>

namespace ApiWithoutSecrets {
	
	namespace OS {
		
	// ************************************************************ //
    // LibraryHandle                                                //
    //                                                              //
    // Dynamic Library OS dependent type                            //
    // ************************************************************ //
    // 
	
	    // 
#if defined(VK_USE_PLATFORM_WIN32_KHR)
    typedef HMODULE LibraryHandle;

#elif defined(VK_USE_PLATFORM_XCB_KHR) || defined(VK_USE_PLATFORM_XLIB_KHR)
    typedef void* LibraryHandle;

#endif

 // ************************************************************ //
    // OnWindowSizeChanged                                          //
    //                                                              //
    // Base class for handling window size changes                  //
    // ************************************************************ //
	

	class TutorialBase {
		
		public:
		
			virtual bool OnWindowSizeChanged() = 0;
			virtual bool Draw() = 0;
			
			virtual bool ReadyToDraw() const final { 
			return CanRender;
			}
			
			TutorialBase():
			CanRender(false) {}
			
			virtual ~TutorialBase() {}
			
		protected:
			bool CanRender;
		
		
	};

	
	// ************************************************************ //
    // WindowParameters                                             //
    //                                                              //
    // OS dependent window parameters                               //
    // ************************************************************ //
	struct WindowParameters {
#if defined(VK_USE_PLATFORM_WIN32_KHR)
      HINSTANCE           Instance;
      HWND                Handle;

      WindowParameters() :
        Instance(),
        Handle() {
      }

#elif defined(VK_USE_PLATFORM_XCB_KHR)
      xcb_connection_t   *Connection;
      xcb_window_t        Handle;

      WindowParameters() :
        Connection(),
        Handle() {
      }

#elif defined(VK_USE_PLATFORM_XLIB_KHR)
      Display            *DisplayPtr;
      Window              Handle;

      WindowParameters() :
        DisplayPtr(),
        Handle() {
      }

#endif
    };

	
	 // ************************************************************ //
    // Window                                                       //
    //                                                              //
    // OS dependent window creation and destruction class           //
    // ************************************************************ //
    class Window {
    public:
      Window();
      ~Window();

      bool              Create( const char *title );
      bool              RenderingLoop( TutorialBase &tutorial ) const;
      WindowParameters  GetParameters() const;

    private:
      WindowParameters  Parameters;
    };
	
	}
}

#endif // OPERATING_SYTEM_HEADER