#include <cstdarg>
#include "StringUtility.h"

#if _Shh_Platform == _Shh_Platform_Win32
#   pragma warning (disable : 4996)
#   pragma warning (disable : 4717)
#endif // _DEBUG
#define __char_cache_size 1024
namespace Shh
{
	namespace utility
	{
	//utf8字符长度1-6，可以根据每个字符第一个字节判断整个字符长度
	//0xxxxxxx
	//110xxxxx 10xxxxxx
	//1110xxxx 10xxxxxx 10xxxxxx
	//11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	//111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	//1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	//
	//定义查找表，长度256，表中的数值表示以此为起始字节的utf8字符长度
	//const unsigned char utf8_look_for_table[] = 
	//{
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	//	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	//	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	//	3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
	//	4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 1, 1
	//};
	//inline unsigned char _getUtf8Len(unsigned char x) 
	//{
	//	return utf8_look_for_table[(x)];
	//}

		void format(String& buff, const char* format, ...)
		{
			char msg[__char_cache_size] = {0};
			va_list arg_ptr;
			va_start(arg_ptr, format);
			int nWrittenBytes = vsprintf_s(msg, __char_cache_size, format, arg_ptr);
			va_end(arg_ptr);
		}


		U8String::size_type character_count(const U8String& str)
		{
			U8String::size_type count = 0;
			U8String::const_iterator begin = str.begin();
			U8String::const_iterator end = str.end();
			while(begin != end)
			{
				const U8String::value_type& ch = *begin;
				if ((ch & _head_mark) != _no_first)
				{
					++count;
				}
				++begin;
			}
			return count;
		}

	void split(StringVector& out, const U8String& str, const U8String& delims, unsigned int maxSplits)
	{
		// Pre-allocate some space for performance
		out.reserve(maxSplits ? maxSplits+1 : 10);    // 10 is guessed capacity for most case

		unsigned int numSplits = 0;

		// Use STL methods 
		size_t start, pos;
		start = 0;
		do 
		{
			pos = str.find_first_of(delims, start);
			if (pos == start)
			{
				// Do nothing
				start = pos + 1;
			}
			else if (pos == U8String::npos || (maxSplits && numSplits == maxSplits))
			{
				// Copy the rest of the string
				out.push_back( str.substr(start) );
				break;
			}
			else
			{
				// Copy up to delimiter
				out.push_back( str.substr(start, pos - start) );
				start = pos + 1;
			}
			// parse up to next real data
			start = str.find_first_not_of(delims, start);
			++numSplits;

		} while (pos != U8String::npos);
	}


	//-----------------------------------------------------------------------
	void tokenise(StringVector& out, const U8String& str, const U8String& singleDelims, const U8String& doubleDelims, unsigned int maxSplits)
	{
		// Pre-allocate some space for performance
		out.reserve(maxSplits ? maxSplits+1 : 10);    // 10 is guessed capacity for most case

		unsigned int numSplits = 0;
		U8String delims = singleDelims + doubleDelims;

		// Use STL methods 
		size_t start, pos;
		utf8 curDoubleDelim = 0;
		start = 0;
		do 
		{
			if (curDoubleDelim != 0)
			{
				pos = str.find(curDoubleDelim, start);
			}
			else
			{
				pos = str.find_first_of(delims, start);
			}

			if (pos == start)
			{
				utf8 curDelim = str.at(pos);
				if (doubleDelims.find_first_of(curDelim) != U8String::npos)
				{
					curDoubleDelim = curDelim;
				}
				// Do nothing
				start = pos + 1;
			}
			else if (pos == U8String::npos || (maxSplits && numSplits == maxSplits))
			{
				if (curDoubleDelim != 0)
				{
					//Missing closer. Warn or throw exception?
				}
				// Copy the rest of the string
				out.push_back( str.substr(start) );
				break;
			}
			else
			{
				if (curDoubleDelim != 0)
				{
					curDoubleDelim = 0;
				}

				// Copy up to delimiter
				out.push_back( str.substr(start, pos - start) );
				start = pos + 1;
			}
			if (curDoubleDelim == 0)
			{
				// parse up to next real data
				start = str.find_first_not_of(singleDelims, start);
			}

			++numSplits;

		} while (pos != U8String::npos);
	}
	//-----------------------------------------------------------------------


	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	bool startsWith(const U8String& str, const U8String& pattern, bool lowerCase)
	{
		size_t thisLen = str.length();
		size_t patternLen = pattern.length();
		if (thisLen < patternLen || patternLen == 0)
			return false;

		U8String startOfThis = str.substr(0, patternLen);
		if (lowerCase)
			toLowerCase(startOfThis);

		return (startOfThis == pattern);
	}
	//-----------------------------------------------------------------------
	bool endsWith(const U8String& str, const U8String& pattern, bool lowerCase)
	{
		size_t thisLen = str.length();
		size_t patternLen = pattern.length();
		if (thisLen < patternLen || patternLen == 0)
			return false;

		U8String endOfThis = str.substr(thisLen - patternLen, patternLen);
		if (lowerCase)
			toLowerCase(endOfThis);

		return (endOfThis == pattern);
	}
	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	void splitFileName(const U8String& qualifiedName, 
		U8String& outBasename, U8String& outPath)
	{
		U8String path = qualifiedName;
		// Replace \ with / first
		std::replace( path.begin(), path.end(), '\\', '/' );
		// split based on final /
		size_t i = path.find_last_of('/');

		if (i == U8String::npos)
		{
			outPath.clear();
			outBasename = qualifiedName;
		}
		else
		{
			outBasename = path.substr(i+1, path.size() - i - 1);
			outPath = path.substr(0, i+1);
		}

	}
	//-----------------------------------------------------------------------
	void splitBaseFileName(const U8String& fullName, 
		U8String& outBasename, U8String& outExtention)
	{
		size_t i = fullName.find_last_of(".");
		if (i == U8String::npos)
		{
			outExtention.clear();
			outBasename = fullName;
		}
		else
		{
			outExtention = fullName.substr(i+1);
			outBasename = fullName.substr(0, i);
		}
	}
	// ----------------------------------------------------------------------------------------------------------------------------------------------
	void splitFullFileName(	const U8String& qualifiedName, 
		U8String& outBasename, U8String& outExtention, U8String& outPath )
	{
		U8String fullName;
		splitFileName( qualifiedName, fullName, outPath );
		splitBaseFileName( fullName, outBasename, outExtention );
	}
	//-----------------------------------------------------------------------
	bool match(const U8String& str, const U8String& pattern, bool caseSensitive)
	{
		U8String tmpStr = str;
		U8String tmpPattern = pattern;
		if (!caseSensitive)
		{
			toLowerCase(tmpStr);
			toLowerCase(tmpPattern);
		}

		U8String::const_iterator strIt = tmpStr.begin();
		U8String::const_iterator patIt = tmpPattern.begin();
		U8String::const_iterator lastWildCardIt = tmpPattern.end();
		while (strIt != tmpStr.end() && patIt != tmpPattern.end())
		{
			if (*patIt == '*')
			{
				lastWildCardIt = patIt;
				// Skip over looking for next character
				++patIt;
				if (patIt == tmpPattern.end())
				{
					// Skip right to the end since * matches the entire rest of the string
					strIt = tmpStr.end();
				}
				else
				{
					// scan until we find next pattern character
					while(strIt != tmpStr.end() && *strIt != *patIt)
						++strIt;
				}
			}
			else
			{
				if (*patIt != *strIt)
				{
					if (lastWildCardIt != tmpPattern.end())
					{
						// The last wildcard can match this incorrect sequence
						// rewind pattern to wildcard and keep searching
						patIt = lastWildCardIt;
						lastWildCardIt = tmpPattern.end();
					}
					else
					{
						// no wildwards left
						return false;
					}
				}
				else
				{
					++patIt;
					++strIt;
				}
			}

		}
		// If we reached the end of both the pattern and the string, we succeeded
		if (patIt == tmpPattern.end() && strIt == tmpStr.end())
		{
			return true;
		}
		else
		{
			return false;
		}

	}

	int lineCount(const char* str)
	{
		if (str)
		{
			int l = 0;
			while(*str != 0)
			{
				if (ASCII_LF == *str)
				{
					++l;
				}
				++str;
			}
			return l;
		}
		return 0;
	}




	}//namespace utility end.
}