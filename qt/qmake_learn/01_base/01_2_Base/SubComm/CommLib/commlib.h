#ifndef COMMLIB_H
#define COMMLIB_H

#include "CommLib_global.h"

class COMMLIB_EXPORT CommLib
{
public:
    CommLib();
    ~CommLib();
    CommLib(const CommLib&) = delete;
    CommLib& operator=(const CommLib) = delete;
    float add(float a, float b)
    {
        return a + b;
    }
    int aa(int bb, int cc)
    {
        return bb - cc;
    }
   int add(int a, int b);
   int Add(int a, int b)
   {
       return a + b;
   }
   void Test();
   bool isOK();

};

COMMLIB_EXPORT float Add(float a, float b);


#endif // COMMLIB_H
