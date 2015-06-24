#ifndef __IRELEASE_H__
#define __IRELEASE_H__
#include "Core/CoreDef.h"
namespace Shh
{
	class _Shh_Export IRelease
	{
	public:
		virtual void Release() = 0;
		virtual ~IRelease(){}
	};

	inline void SafeRelease(IRelease* x) 
	{
		if (x) 
		{ 
			x->Release(); 
		}
	}
}

#endif //__IRELEASE_H__
