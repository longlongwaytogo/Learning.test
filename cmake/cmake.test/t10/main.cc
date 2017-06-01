#include <stdio.h>
#include <stdlib.h>
#include "config.h"

#ifdef USE_MYMATH
  #include "math/MathFunctions.h"
#else
  #include <math.h>
#endif


int main(int argc, char *argv[])
{
  if (argc < 2){
        // print version info
        printf("%s Version %d.%d\n",
            argv[0],
            VERSION_MAXJOR,
            VERSION_MINJOR);
        printf("Usage: %s base exponent \n", argv[0]);
        return 1;
    }

    double base = atof(argv[1]);
 
	 double result = 0.0;
#ifdef USE_MYMATH
    printf("Now we use our own Math library. \n");
   // double result = power(base, exponent);
	 result = mysqrt(base);
#else
	  result = sqrt(base);
    printf("Now we use the standard library. \n");
    printf("%d sqrt:%f\n", base, result);
#endif
    
   // printf("%f sqrt:%f\n", base, result);
	 fprintf(stdout, "The square root of %g is %g\n", base, result);
    return 0;
}
