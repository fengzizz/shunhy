#include "HString.h"

namespace Shh
{
	hstring::hstring()
		:_hash_code(0)
	{

	}

	hstring::hstring(const hstring& copy)
	{
		_from(copy);
	}

	hstring::hstring(const utf8* str)
	{
		set(str);
	}

	void hstring::set(const utf8* str)
	{
		_string = str;
		_hash();
	}

	void hstring::set(const U8String& str)
	{
		_string = str;
		_hash();
	}

	const hstring& hstring::operator = (const hstring& copy)
	{
		_from(copy);
		return *this;
	}

	ulong hstring::hash_string(const utf8* str)
	{
		// BKDR Hash 
		ulong seed = 131; // 31 131 1313 13131 131313 etc..
		ulong hash = 0;

		while (*str)
		{
			hash = hash * seed + (*str++);
		}

		return (hash & 0x7FFFFFFF);
	}
	void hstring::_hash()
	{
		if (_string.size())
		{
			_hash_code = hash_string(_string.c_str());
		}
		else
		{
			_hash_code = 0;
		}
	}

	void hstring::_from(const hstring& copy)
	{
		_string = copy._string;
		_hash_code = copy._hash_code;
	}

	void hstring::_from(const U8String& copy)
	{
		_string = copy;
		_hash();
	}
}