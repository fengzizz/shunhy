#ifndef __SHH_STRING_UTILITY_H_
#define __SHH_STRING_UTILITY_H_
#include <vector>
#include <codecvt>
#include <algorithm>
#include "U16String.h"
#include "U8String.h"

namespace Shh
{
	namespace utility
	{
		typedef std::vector<U8String> StringVector;

		U8String::size_type _Shh_Export character_count(const U8String& str);

		void _Shh_Export format(String& buff, const char* format, ...);


		inline void trim(U8String& str, bool left = true, bool right = true)
		{
			/*
			size_t lspaces, rspaces, len = length(), i;

			lspaces = rspaces = 0;

			if( left )
			{
				// Find spaces / tabs on the left
				for( i = 0;
					i < len && ( at(i) == ' ' || at(i) == '\t' || at(i) == '\r');
					++lspaces, ++i );
			}
        
			if( right && lspaces < len )
			{
				// Find spaces / tabs on the right
				for( i = len - 1;
					i >= 0 && ( at(i) == ' ' || at(i) == '\t' || at(i) == '\r');
					rspaces++, i-- );
			}

			*this = substr(lspaces, len-lspaces-rspaces);
			*/
			static const U8String delims = " \t\r";
			if(right)
				str.erase(str.find_last_not_of(delims)+1); // trim right
			if(left)
				str.erase(0, str.find_first_not_of(delims)); // trim left
		}

		/** Returns a StringVector that contains all the substrings delimited
			by the characters in the passed <code>delims</code> argument.
			@param
				delims A list of delimiter characters to split by
			@param
				maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
				parameters is > 0, the splitting process will stop after this many splits, left to right.
		*/
		void _Shh_Export split(StringVector& out, const U8String& str, const U8String& delims = "\t\n ", unsigned int maxSplits = 0);

		/** Returns a StringVector that contains all the substrings delimited
			by the characters in the passed <code>delims</code> argument, 
			or in the <code>doubleDelims</code> argument, which is used to include (normal) 
			delimeters in the tokenised string. For example, "strings like this".
			@param
				delims A list of delimiter characters to split by
			@param
				delims A list of double delimeters characters to tokenise by
			@param
				maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
				parameters is > 0, the splitting process will stop after this many splits, left to right.
		*/
		void _Shh_Export tokenise(StringVector& out, const U8String& str, const U8String& delims = "\t\n ", const U8String& doubleDelims = "\"", unsigned int maxSplits = 0);

		/** Lower-cases all the characters in the string.
		*/
		inline void toLowerCase(U8String& str)
		{
			std::transform(
				str.begin(),
				str.end(),
				str.begin(),
				tolower);
		}

		/** Upper-cases all the characters in the string.
		*/
		inline void toUpperCase(U8String& str) 
		{
			std::transform(
				str.begin(),
				str.end(),
				str.begin(),
				toupper);
		}


		/** Returns whether the string begins with the pattern passed in.
		@param pattern The pattern to compare with.
		@param lowerCase If true, the start of the string will be lower cased before
			comparison, pattern should also be in lower case.
		*/
		bool _Shh_Export startsWith(const U8String& str, const U8String& pattern, bool lowerCase = true);

		/** Returns whether the string ends with the pattern passed in.
		@param pattern The pattern to compare with.
		@param lowerCase If true, the end of the string will be lower cased before
			comparison, pattern should also be in lower case.
		*/
		bool _Shh_Export endsWith(const U8String& str, const U8String& pattern, bool lowerCase = true);

		/** Method for standardising paths - use forward slashes only, end with slash.
		*/
		inline U8String standardisePath(const U8String& init)
		{
			U8String path = init;

			std::replace( path.begin(), path.end(), '\\', '/' );
			if( path[path.length() - 1] != '/' )
				path += '/';

			return path;
		}

		/** Method for splitting a fully qualified filename into the base name
			and path.
		@remarks
			Path is standardised as in standardisePath
		*/
		void _Shh_Export splitFileName(const U8String& qualifiedName,
			U8String& outBasename, U8String& outPath);

		/** Method for splitting a fully qualified filename into the base name,
		extension and path.
		@remarks
		Path is standardised as in standardisePath
		*/
		void _Shh_Export splitFullFileName(const U8String& qualifiedName, 
			U8String& outBasename, U8String& outExtention, 
			U8String& outPath);

		/** Method for splitting a filename into the base name
		and extension.
		*/
		void _Shh_Export splitBaseFileName(const U8String& fullName, 
			U8String& outBasename, U8String& outExtention);


		/** Simple pattern-matching routine allowing a wildcard pattern.
		@param str U8String to test
		@param pattern Pattern to match against; can include simple '*' wildcards
		@param caseSensitive Whether the match is case sensitive or not
		*/
		bool _Shh_Export match(const U8String& str, const U8String& pattern, bool caseSensitive = true);


		/** replace all instances of a sub-string with a another sub-string.
		@param source Source string
		@param replaceWhat Sub-string to find and replace
		@param replaceWithWhat Sub-string to replace with (the new sub-string)
		@returns An updated string with the sub-string replaced
		*/
		inline U8String replaceAll(const U8String& source, const U8String& replaceWhat, const U8String& replaceWithWhat)
		{
			U8String result = source;
			U8String::size_type pos = 0;
			while(1)
			{
				pos = result.find(replaceWhat,pos);
				if (pos == U8String::npos) break;
				result.replace(pos,replaceWhat.size(),replaceWithWhat);
				pos += replaceWithWhat.size();
			}
			return result;
		}

		int lineCount(const char* str);

		inline int lineCount(const U8String& str)
		{
			return lineCount(str.c_str());
		}

		/// Constant blank string, useful for returning by ref where local does not exist
		static const U8String BLANK;

		static const unsigned char _no_first = 0x80; // 1000 0000
		static const unsigned char _head_mark = 0xc0; // 1100 0000
	}
}
#endif	//__SHH_STRING_UTILITY_H_

