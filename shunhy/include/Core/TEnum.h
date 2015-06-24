#ifndef __SHH_ENUM_H__
#define __SHH_ENUM_H__
#include "U8String.h"


namespace Shh{
	class TEnumSuite;
	class TEnumConvertMap;
	class _Shh_Export TEnumSuite
	{
	public:
		U8String name;
		int code;
		U8String lowername;
		TEnumSuite(TEnumConvertMap& map, const char* n, int c);
		TEnumSuite(TEnumConvertMap& map, const char* n, int c, bool ctoname);
		friend class TEnumConvertMap;
	};

	class _Shh_Export TEnumConvertMap
	{
	public:
		bool parseString(const U8String& _str, int& _e);
		bool parseEnum(int _e, U8String& _str);
		friend class TEnumSuite;
	private:		
		typedef const U8String* StringType;	
		class StringPtrLess
		{
		public:
			bool operator()(const StringType& lIndex, const StringType& rIndex) const;
		};
		typedef std::map<StringType, TEnumSuite*, StringPtrLess> StringToInt;
		typedef std::map<int, TEnumSuite*> IntToString;

		StringToInt stoimap;
		IntToString itosmap;
	};
}



#define __Declare_Enum\
	public:\
			enum Enum
#define __Declare_Enum_Struct(_Ty, _Default)\
public:\
	inline _Ty() :\
	_enum((_Ty::Enum)_Default)\
	{\
	}\
	inline _Ty(_Ty::Enum e) :\
	_enum(e)\
	{\
	}\
	inline friend bool operator < (_Ty const& a, _Ty const& b)\
	{\
	return (a._enum < b._enum);\
	}\
	inline friend bool operator >= (_Ty const& a, _Ty const& b)\
	{\
	return !(a._enum < b._enum);\
	}\
	inline friend bool operator > (_Ty const& a, _Ty const& b)\
	{\
	return (b._enum < a._enum);\
	}\
	inline friend bool operator <= (_Ty const& a, _Ty const& b)\
	{\
	return !(a._enum > b._enum);\
	}\
	inline friend bool operator == (_Ty const& a, _Ty const& b)\
	{\
	return !(a._enum < b._enum) && !(a._enum > b._enum);\
	}\
	inline friend bool operator != (_Ty const& a, _Ty const& b)\
	{\
	return !(a._enum == b._enum);\
	}\
	inline size_t toValue() const\
	{\
		return (size_t)this->_enum;\
	}\
	inline _Ty::Enum getEnum() const\
	{\
		return this->_enum;\
	}\
private:\
	Enum _enum;\


#define __Declare_Enum_Struct_With_Map(_Ty, _Default)\
		__Declare_Enum_Struct(_Ty, _Default)\
	public: \
		inline static const Shh::TEnumConvertMap& GetConvertMap()\
		{\
			return _convertMap;\
		}\
		inline static Shh::TEnumConvertMap& _GetConvertMap()\
		{\
			return _convertMap;\
		}\
		private:\
		static Shh::TEnumConvertMap _convertMap;\

#define __Implement_Enum(_Ty) \
	Shh::TEnumConvertMap Shh::##_Ty##::_convertMap;

#define __Declare_Enum_Map(_Name) Shh::TEnumSuiteMap _Name

#define __Regist_Enum_Suite(_Ty, _Enum) \
	static const Shh::TEnumSuite shh##_Ty##__##_Enum(Shh::##_Ty##::_GetConvertMap(), #_Enum, (int)Shh::##_Ty::_Enum);

#define __Regist_Enum_Suite2(_Ty, _Enum, _SortName) \
	__Regist_Enum_Suite(_Ty, _Enum);\
	static const Shh::TEnumSuite shh##_Ty##__##_Enum##_Name(Shh::##_Ty##::_GetConvertMap(), #_SortName, (int)Shh::##_Ty::_Enum, false);



#endif //__SHH_VARTYPE_H__