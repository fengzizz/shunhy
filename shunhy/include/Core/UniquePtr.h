#ifndef __CORE_UNIQUEPTR_H__
#define __CORE_UNIQUEPTR_H__
#include "Core/CoreDef.h"
namespace
{
#define __IN_LINE__ __forceinline
	// verify that types are complete for increased safety

	template<typename _Ty> __IN_LINE__ void checked_complete(_Ty * x)
	{
		// intentionally complex - simplification causes regressions
		typedef char type_must_be_complete[ sizeof(_Ty)? 1: -1 ];
		(void) sizeof(type_must_be_complete);
	}

	template<typename _Ty>
	class _Shh_Export_Tmpl uptr
	{
	public:
		typedef _Ty* pointer;
		__IN_LINE__ uptr()
			:mPtr(nullptr)
		{

		}
		__IN_LINE__ ~uptr()
		{
			checked_complete(mPtr);
			_Ty::DeleteT(mPtr);
		}

		__IN_LINE__ void create()
		{
			shh_assert(nullptr == mPtr);
			mPtr = _Ty::CreateT();
		}
		__IN_LINE__ void set_null()
		{
			checked_complete(mPtr);
			_Ty::DeleteT(mPtr);
			mPtr = nullptr;
		}

		__IN_LINE__ _Ty & operator*() const // never throws
		{
			shh_assert( nullptr != mPtr );
			return *mPtr;
		}

		__IN_LINE__ _Ty * operator->() const // never throws
		{
			shh_assert( nullptr != mPtr );
			return mPtr;
		}

		__IN_LINE__ _Ty * get() const // never throws
		{
			return mPtr;
		}

		__IN_LINE__ bool empty() const
		{
			return nullptr == mPtr;
		}

		__IN_LINE__ bool exist() const
		{
			return nullptr != mPtr;
		}
		
	private:


		pointer mPtr;
		uptr(uptr const &);
		uptr & operator=(uptr const &);
		typedef uptr<_Ty> this_type;
		void operator==( uptr const& ) const;
		void operator!=( uptr const& ) const;
	};
}

#endif //__CORE_UNIQUEPTR_H__