#ifndef __CORE_CORECONFIG_H__
#define __CORE_CORECONFIG_H__
#ifndef nullptr
#define nullptr 0
#endif
#ifndef override
#define override
#endif
#ifndef final
#define final
#endif

#define _Shh_Platform_Unknown 0
#define _Shh_Platform_Windows 1
#define _Shh_Platform_Android 2
#define _Shh_Platform_IOS 3

#define _Shh_Compiler_Unknown 0
#define _Shh_Compiler_MSVC 1
#define _Shh_Compiler_GNUC 2
#define _Shh_Compiler_BORL 3
#define _Shh_Compiler_WINSCW 4
#define _Shh_Compiler_GCCE 5



#ifdef __SHH_LINK_AS_DLL__
#	define _Shh_Call __cdecl
#	ifdef __SHH_EXPORT_API__
#		define _Shh_Export __declspec(dllexport)
#		define _Shh_Export_Tmpl //__declspec(dllexport)
#	else
#		define _Shh_Export __declspec(dllimport)
#		define _Shh_Export_Tmpl
#	endif
#else
#	define _Shh_Call 
#	define _Shh_Export 
#	define _Shh_Export_Tmpl
#endif

#if defined(WIN32)
#	define _Shh_Platform _Shh_Platform_Windows
#endif


#if _WIN64
#	define _Shh_Platform_64Bits 1
#elif _WIN32 
#	define  _Shh_Platform_32Bits 1
#endif


#if defined( _MSC_VER )
#   define _Shh_Compiler _Shh_Compiler_MSVC
#endif

#if _Shh_Compiler == _Shh_Compiler_MSVC
// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)
#endif


// GCC settings
#if defined __GNUC__
#define __cdecl
#define __forceinline inline
#endif


#define __Renderer_d3d9__ 0
#define __Renderer_d3d11__ 1
#define __Renderer_gles__ 0


// config check
#if _Shh_Platform_64Bits
#	if _Shh_Platform_32Bits
#		error(confused platform bits")
#	endif
#elif _Shh_Platform_32Bits
#	if _Shh_Platform_64Bits
#		error("confused platform bits")
#	endif
#else
#	error("unknown platform bits")
#endif

#if _Shh_Platform == _Shh_Platform_Unknown
#	error("unknown platform")
#else
#	ifndef _Shh_Platform
#		error("unknown platform")
#	endif
#endif

#if _Shh_Compiler == _Shh_Compiler_Unknown
#	error("unknown compiler")
#else
#	ifndef _Shh_Compiler
#		error("unknown compiler")
#	endif
#endif

#endif // __CORE_CORECONFIG_H__
