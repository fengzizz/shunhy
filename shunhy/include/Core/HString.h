#ifndef __SHH_HSTRING_H_
#define __SHH_HSTRING_H_
#include "CoreDef.h"
#include "U8String.h"

namespace Shh
{
	class hstring;
	typedef hstring HString;
	class _Shh_Export hstring final
	{
	public:
		typedef U8String string_type;
		hstring();
		hstring(const hstring& copy);
		hstring(const utf8* str);

		void set(const U8String& str);
		void set(const utf8* str);
		const string_type& string() const;
		const string_type::value_type* c_str() const;

		bool equal(const utf8* str) const;		
		bool equal(const hstring& str) const;
		bool equal(const U8String& str) const;

		const hstring& operator = (const hstring& copy);
		bool operator == (const hstring& rv) const;
		bool operator != (const hstring& rv) const;
		bool operator < (const hstring& rv) const;
		bool operator > (const hstring& rv) const;

		static ulong hash_string(const utf8* str);
		static hstring from(const U8String& str);
	private:
		void _from(const hstring& copy);
		void _from(const U8String& copy);
		void _hash();
		ulong _hash_code;
		string_type _string;
	};

	inline bool hstring::equal(const utf8* str) const
	{
		return _string == str;
	}
	inline bool hstring::equal(const hstring& str) const
	{
		return (_hash_code == str._hash_code) && (_string == str._string);
	}
	inline bool hstring::equal(const U8String& str) const
	{
		return _string == str;
	}


	inline bool hstring::operator == (const hstring& rv) const
	{
		return (_hash_code == rv._hash_code) && (_string == rv._string);
	}

	inline bool hstring::operator != (const hstring& rv) const
	{
		return (_hash_code != rv._hash_code) || (_string != rv._string);
	}

	inline bool hstring::operator < (const hstring& rv) const
	{
		if (rv._hash_code == _hash_code)
		{
			return _string < rv._string;
		}
		return _hash_code < rv._hash_code;
	}

	inline bool hstring::operator > (const hstring& rv) const
	{
		if (rv._hash_code == _hash_code)
		{
			return _string > rv._string;
		}
		return _hash_code > rv._hash_code;
	}

	inline const hstring::string_type& hstring::string() const
	{
		return _string;
	}

	inline const hstring::string_type::value_type* hstring::c_str() const
	{
		return string().c_str();
	}

	inline hstring hstring::from(const U8String& str)
	{
		hstring h;
		h._from(str);
		return h;
	}
}


#endif //__SHH_HSTRING_H_