#include <iostream>
#include <string>
#include "../inc/hello.h"
#include <Foo.h>
int  main(int argc, char** argv)
{
	//hello();
	//hello();
	hello("adfggfsdfsfs");
	std::cout<<"hello world!"<<std::endl;
	std::string  projectName = "testCmake";
	std::cout<<" project name:"<<projectName<<std::endl;
	
	if (argc < 2)
    {
    fprintf(stdout,"%s Version %d.%d\n",
            argv[0],
            Tutorial_VERSION_MAJOR,
            Tutorial_VERSION_MINOR);
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }
  double inputValue = atof(argv[1]);
  double outputValue = sqrt(inputValue);
  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);

  return 0;
		  
}