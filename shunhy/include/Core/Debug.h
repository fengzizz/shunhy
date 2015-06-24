#ifndef __CORE_DEBUG_H__
#define __CORE_DEBUG_H__
#include "Core/U8String.h"
#include "Core/Exceptions.h"
namespace Shh
{
	void _Shh_Export _DebugOutput(const char* ouput);
	void _Shh_Export _DebugOutputLine(const char* ouput);


#define debug_output(x) Shh::_DebugOutput(x);
#define debug_output_line(x) Shh::_DebugOutputLine(x)

}

#endif //__CORE_DEBUG_H__