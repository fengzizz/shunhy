#include "TEnum.h"
#include "StringUtility.h"
namespace Shh
{
	TEnumSuite::TEnumSuite(TEnumConvertMap& map, const char* n, int c)
		:name(n)
		,code(c)
	{
		lowername = name;
		utility::toLowerCase(lowername);
		map.stoimap[&lowername] = this;
		map.itosmap[code] = this;
	}

	TEnumSuite::TEnumSuite(TEnumConvertMap& map, const char* n, int c, bool ctoname)
		:name(n)
		,code(c)
	{
		lowername = name;
		utility::toLowerCase(lowername);
		map.stoimap[&lowername] = this;
		if (ctoname)
		{
			map.itosmap[code] = this;
		}
	}
	bool TEnumConvertMap::StringPtrLess::operator()(const StringType& lIndex, const StringType& rIndex) const
	{
		return *lIndex < *rIndex;
	}

	bool TEnumConvertMap::parseString(const U8String& _str, int& _e)
	{
		U8String lower = _str;
		utility::toLowerCase(lower);
		StringToInt::const_iterator it = stoimap.find(&lower);
		if (it != stoimap.end())
		{
			_e = it->second->code;
			return true;
		}
		return false;
	}
	bool TEnumConvertMap::parseEnum(int _e, U8String& _str)
	{
		IntToString::const_iterator it = itosmap.find(_e);
		if (it != itosmap.end())
		{
			_str = it->second->name;
			return true;
		}
		return false;
	}
}