#ifndef KERNELCOMMONUSE_H
#define KERNELCOMMONUSE_H

#include "KernelCommonUse_global.h"

class KERNELCOMMONUSE_EXPORT KernelCommonUse
{
public:
    KernelCommonUse();

    int add(int a, int b);
};

extern "C" KERNELCOMMONUSE_EXPORT int add(int a, int b);

#endif // KERNELCOMMONUSE_H
