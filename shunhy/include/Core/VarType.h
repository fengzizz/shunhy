#ifndef __SHH_VARTYPE_H__
#define __SHH_VARTYPE_H__

namespace Shh
{
	typedef char				int8;
	typedef short int			int16;
	typedef int					int32;
	typedef	long long			int64;
	typedef float				Single;
	typedef double				Double;

	typedef unsigned char		uchar;
	typedef uchar				uint8;
	typedef unsigned short		uint16;
	typedef unsigned int		uint32;
	typedef unsigned long long	uint64;

	typedef unsigned int		uint;
	typedef unsigned long		ulong;

	typedef uchar				byte;
	typedef char				utf8;
	typedef unsigned short		utf16;

	typedef void*				pointer;

#define OUT
#define IN

#define Float_Max			3.402823E+38f
#define Float_Min			-3.402823E+38f
#define U8HEAD0 0xef
#define U8HEAD1 0xbb
#define U8HEAD2 0xbf
#define ASCII_TAB 9
#define ASCII_LF 10
#define ASCII_CR 13
const int Invalid_Index	= -1;
const int Invalid_Count = -1;
}
#endif //__SHH_VARTYPE_H__