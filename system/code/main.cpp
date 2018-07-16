

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <ProcessThreadsApi.h>
#include <type_traits>
#include <iostream>

#include "Lambda.hpp"

template< class T >
std::size_t alignment_of_v = alignment_of<T>::value;
void main()
{
		
	{
		// resrict
		int ar[10];
		int * __restrict restar = (int *)malloc(10 * sizeof(int));
		int * par = ar;

		for (int n = 0; n < 10; n++)
		{
			par[n] += 5;
			restar[n] += 5;
			ar[n] *= 2;
			par[n] += 3;
			restar[n] += 3;
		}
		

	}
#ifdef _M_AMD64
#define LOCK_FREE_LINKED_LIST_DOUBLE_SIZE_PTR_ALIGN 16
#else 
#define LOCK_FREE_LINKED_LIST_DOUBLE_SIZE_PTR_ALIGN 8
#endif 

#define CRY_ALIGN(bytes) __declspec(align(bytes))
	struct SLockFreeSingleLinkedListEntry
	{
		CRY_ALIGN(LOCK_FREE_LINKED_LIST_DOUBLE_SIZE_PTR_ALIGN) SLockFreeSingleLinkedListEntry * volatile pNext;
	};
	static_assert(std::alignment_of<SLockFreeSingleLinkedListEntry>::value == sizeof(uintptr_t) * 2, "Alignment failure for SLockFreeSingleLinkedListEntry");


	{

		// test lock
	}
	class A {};
	

	int val = std::alignment_of<SLockFreeSingleLinkedListEntry>::value;
	std::cout << "val:" << val << std::endl;
	std::cout << "sizeof A:" << sizeof(A) << '\n';
	std::cout << std::alignment_of<A>::value << '\n';
	std::cout << std::alignment_of<int>() << '\n'; // alt syntax
	std::cout << std::alignment_of_v<double> << '\n'; // c++17 alt syntax



	// create name for thread
	const DWORD MS_VC_EXCEPTION = 0x406D1388;

	struct SThreadNameDesc
	{
		DWORD  dwType;      // Must be 0x1000.
		LPCSTR szName;      // Pointer to name (in user addr space).
		DWORD  dwThreadID;  // Thread ID (-1=caller thread).
		DWORD  dwFlags;     // Reserved for future use, must be zero.
	};

	SThreadNameDesc info;
	info.dwType = 0x1000;
	info.szName = "main_Thread";
	DWORD hr = GetCurrentThreadId();
	info.dwThreadID = GetCurrentThreadId();
	info.dwFlags = 0;
#pragma warning(push)
#pragma warning(disable : 6312 6322)
	// warning C6312: Possible infinite loop: use of the constant EXCEPTION_CONTINUE_EXECUTION in the exception-filter expression of a try-except
	// warning C6322: empty _except block
	__try
	{
		// Raise exception to set thread name for attached debugger
		RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(DWORD), (ULONG_PTR*)&info);
	}
	__except (GetExceptionCode() == MS_VC_EXCEPTION ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_EXECUTE_HANDLER)
	{
	}
#pragma warning(pop)

	char buf[255] = {0};
	CONTEXT context;
	GetThreadContext(GetCurrentThread(),&context);
	

//	HRESULT hr = GetThreadDescription(ThreadHandle, &data);
//	if (SUCCEEDED(hr))
//	{   
//		wprintf(¡°%ls\m¡±, data);
//		LocalFree(data);
//	}
//





}