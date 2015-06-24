#ifndef __DEBUGLISTENER_H__
#define __DEBUGLISTENER_H__
#include "CoreDef.h"
namespace Shh
{
	class _Shh_Export DebugListener
	{
	public:
		virtual ~DebugListener(){}
		virtual void AddOutput(char* output) = 0;
	};
}

#endif //__DEBUGLISTENER_H__