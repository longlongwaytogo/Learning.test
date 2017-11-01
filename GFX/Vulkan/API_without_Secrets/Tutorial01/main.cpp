#include "Tutorial01.h"


int main( int argc, char ** argv ) {

	ApiWithoutSecrets::OS::Window window;
	ApiWithoutSecrets::Tutorial01 tutorial01;


	// window creation
	if(! window.Create("01-The Beginning") ) {
		return -1;
	}
	
	// Vulkan preparations and initialization
	if( !tutorial01.PrepareVulkan() ) { 
		return -1;
	}
	
	// Rendering Loop
	
	if(!window.RenderingLoop(tutorial01) ) { 
		return -1;
	
	}

	return 0;

}