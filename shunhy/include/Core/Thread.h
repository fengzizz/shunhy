#ifndef __CORE_THREAD_H__
#define __CORE_THREAD_H__
#include "Core/CoreDef.h"

namespace Shh
{
	__forceinline long _Increment(long volatile& var)
	{
		return _InterlockedIncrement((volatile long*)&var);
	}

	__forceinline long _Decrement(long volatile& var)
	{
		return _InterlockedDecrement((volatile long*)&var);
	}

	__forceinline int _Increment(int volatile& var)
	{
		return (int)_InterlockedIncrement((volatile long*)&var);
	}

	__forceinline int _Decrement(int volatile& var)
	{
		return (int)_InterlockedDecrement((volatile long*)&var);
	}
	__forceinline int _Exchange(int volatile& var1, int var2)
	{
		return (int)_InterlockedExchange((volatile long*)&var1, var2);
	}
}

#endif //__CORE_THREAD_H__