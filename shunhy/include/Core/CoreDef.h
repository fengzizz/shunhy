#ifndef __CORE_COREDEF_H__
#define __CORE_COREDEF_H__
#include <cassert>
#include <string>
#include <map>
#include <vector>

#define STRUCT_DATA_SET(Type, SubType, var) inline void Set##Type##var(const SubType& value) { m##Type.var = value;}
	

#define __Super(ParentClass) \
		public: typedef ParentClass super; \
		private:\


#define __NoCopy(ClassType)\
private:\
	ClassType(ClassType const &);\
	ClassType & operator=(ClassType const &);\
	void operator==( ClassType const& ) const;\
	void operator!=( ClassType const& ) const;

#define shh_new new
#define shh_delete delete

#define shh_assert(x) assert(x)

#if _DEBUG
# define shh_assert2(x, msg) { if (!(x)) assert(msg);}
#else
# define shh_assert2(x, msg) 
#endif


#define __Dynamic_Alloc(T) \
	public:\
	static T* CreateT()\
		{\
		return shh_new T();\
		}\
		static void DeleteT(T* ptr)\
		{\
		shh_delete ptr;\
		}\
	private:

#define __for_each(container, array, elem)\
for(container::const_iterator elem = array.begin(), ____end____ = array.end(); elem != ____end____; ++elem)

#include "Core/CoreConfig.h"
#include "Core/VarType.h"


namespace Shh
{

	typedef std::string String;	
	class SharedObject;
	class CoreService;
	class DebugListener;
	class MemoryBlock;
	class LogLevel;
}
#endif // __CORE_COREDEF_H__
