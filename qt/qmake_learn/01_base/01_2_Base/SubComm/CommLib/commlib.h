#ifndef COMMLIB_H
#define COMMLIB_H

#include "CommLib_global.h"

class COMMLIB_EXPORT CommLib
{
public:
    CommLib();

   int add(int a, int b);
   void Test()
   {

   }

   bool isOK()
   {
       return false;
   }
};

COMMLIB_EXPORT float Add(float a, float b);


#endif // COMMLIB_H
