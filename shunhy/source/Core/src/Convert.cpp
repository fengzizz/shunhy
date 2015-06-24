#include <codecvt>
#include <sstream>
#include "U16String.h"
#include "U8String.h"
#include "StringUtility.h"
#include "Convert.h"
namespace Shh
{
namespace utility
{
	void toUtf16(const U8String& _u8, U16String& _u16)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<U16String::value_type>, U16String::value_type> convert;

		_u16 = convert.from_bytes(_u8);
	}
	void toUtf16(const utf8* _u8, U16String& _u16)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<U16String::value_type>, U16String::value_type> convert;

		_u16 = convert.from_bytes(_u8);
	}

	void toUtf8(const U16String& _u16, U8String& _u8)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<U16String::value_type>, U16String::value_type > convert;

		_u8 = convert.to_bytes(_u16);
	}

	void toUtf8(const utf16* _u16, U8String& _u8)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<U16String::value_type>, U16String::value_type > convert;

		_u8 = convert.to_bytes(_u16);
	}
	template<typename _Vt>
	inline _Vt toValue(const char* str)
	{
		std::stringstream convert(str);
		_Vt tmp = 0;
		convert>>tmp;
		return tmp;
	}

	template<typename _Vt>
	inline bool parseValue(const U8String& str, _Vt& value)
	{
		std::stringstream convert(str);
		value = 0;
		return convert>>value &&
		(convert >> std::ws).eof();
	}

	bool parseBool(const U8String& _str, bool& result)
	{
		U8String lower = _str;
		utility::toLowerCase(lower);
		static const char* bools[] = {
			//  0     1      10     11    100      101
			"no", "yes", "off", "on", "false", "true", 0
		};
		size_t i = 0;
		while (bools[i] != 0)
		{
			if (0 == strcmp(bools[i], lower.c_str()))
			{
				result = 1 == (i & 1);
				return true;
			}
			++i;
		}
		result = false;
		return false;
	}

	bool parseInt(const U8String& _str, int& result)
	{
		return parseValue(_str, result);
	}

	bool parseUInt8(const U8String& _str, uint8& result)
	{
		return parseValue(_str, result);
	}

	bool parseFloat(const U8String& _str, float& result)
	{
		U8String _tmp = _str;
		utility::trim(_tmp);
		if ('f' == _tmp.back() || 'F' == _tmp.back())
		{
			_tmp.pop_back();
		}
		return parseValue(_tmp, result);
	}

	bool parseSingle(const U8String& _str, Single& result)
	{
		U8String _tmp = _str;
		utility::trim(_tmp);
		if ('f' == _tmp.back() || 'F' == _tmp.back())
		{
			_tmp.pop_back();
		}
		return parseValue(_tmp, result);
	}

	bool parseDouble(const U8String& _str, double& result)
	{
		return parseValue(_str, result);
	}




	int toInt(const char* str)
	{
		return toValue<int>(str);
		//return atoi(str);
	}
	
	float toFloat(const char* str)
	{
		return toValue<float>(str);
		//return (float)atof(str);
	}

	double toDouble(const char* str)
	{
		return toValue<double>(str);
		//return atof(str);
	}

	bool toBool(const U8String& str)
	{
		bool result;
		parseBool(str, result);
		return result;
	}


}
#ifndef u8
	__u8__::__u8__()
		:__temp_u8(nullptr)
	{

	}
	__u8__::~__u8__()
	{
		shh_delete __temp_u8;
		__temp_u8 = nullptr;
	}

	const utf8* __u8__::operator = (const utf16* u16)
	{
		if (nullptr == __temp_u8)
		{
			__temp_u8 = shh_new U8String();
		}
		utility::toUtf8(u16, *__temp_u8);
		return __temp_u8->c_str();
	}
#endif

}