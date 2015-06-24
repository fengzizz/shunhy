#ifndef __STRING_CONVERT_COREDEF_H__
#define __STRING_CONVERT_COREDEF_H__

#include "Core/CoreDef.h"
#include "Core/U8String.h"
#include "Core/U16String.h"
namespace Shh
{
	namespace utility
	{
		void _Shh_Export toUtf16(const U8String& _u8, U16String& _u16);
		void _Shh_Export toUtf16(const utf8* _u8, U16String& _u16);

		void _Shh_Export toUtf8(const U16String& _u16, U8String& _u8);
		void _Shh_Export toUtf8(const utf16* _u16, U8String& _u8);

		int _Shh_Export toInt(const char* str);

		float _Shh_Export toFloat(const char* str);

		double _Shh_Export toDouble(const char* str);

		bool _Shh_Export toBool(const U8String& str);

		inline int toInt(const U8String& str)
		{
			return toInt(str.c_str());
		}

		inline float toFloat(const U8String& str)
		{
			return toFloat(str.c_str());
		}

		inline double toDouble(const U8String& str)
		{
			return toDouble(str.c_str());
		}

		bool _Shh_Export parseBool(const U8String& _str, bool& result);

		bool _Shh_Export parseInt(const U8String& _str, int& result);

		bool _Shh_Export parseUInt8(const U8String& _str, uint8& result);

		bool _Shh_Export parseFloat(const U8String& _str, float& result);

		bool _Shh_Export parseSingle(const U8String& _str, Single& result);

		bool _Shh_Export parseDouble(const U8String& _str, double& result);
	};

#define __UTEXT(quote) (const utf16*)L##quote
#define UTEXT(quote) __UTEXT(quote)

#ifndef u8
	class _Shh_Export __u8__ final
	{
		__NoCopy(__u8__);
	public:
		__u8__();
		~__u8__();
		const Shh::utf8* operator = (const Shh::utf16* u16); 
	private:
		Shh::U8String* __temp_u8;
	};

#define U8TEXT(quote) Shh::__u8__()=UTEXT(quote)
#else
#define __u8(quote) u8##quote
#define U8TEXT(quote) __u8(quote)
#endif
}


#endif //__STRING_CONVERT_COREDEF_H__