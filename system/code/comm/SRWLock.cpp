#include <windows.h>
#include <synchapi.h>
#include "SRWLock.h"

MultiThreads::detail::MT_SRWLOCK::MT_SRWLOCK():SRWLock_(0)
{
	static_assert(sizeof(SRWLock_) == sizeof(PSRWLOCK), "RWLock-pointer has invalid size");
	InitializeSRWLock(reinterpret_cast<PSRWLOCK>(&SRWLock_));
}

