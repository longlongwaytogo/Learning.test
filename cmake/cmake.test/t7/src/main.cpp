#include <iostream>
#include <string>
#include "../config.h"
#include <stdlib.h>
#include <stdio.h>


void main()
{
	
	
#ifdef USE_OPTION	
	std::cout<< "use Option on."<<std::endl;
#else 
	std::cout<< " use Option off."<<std::endl;
#endif 
	std::cout<<" t7 test"<<std::endl;

#ifdef HAVE_PRINTF
   std::cout<< "have printf"<<std::endl;
  int d = 100;
   printf("%s,%d","use printf",d);
#else 
   std::cout<< " not have printf"<<std::endl;
#endif
	
}