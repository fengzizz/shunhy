

#ifndef __SHARED_OBJECT_H__
#define __SHARED_OBJECT_H__

#include "Core/Thread.h"

namespace Shh
{
	class _Shh_Export SharedObject
	{
	public:
		/// constructor
		SharedObject();

		/// get the current refcount
		int RefCount() const;

		bool Shared() const;

		bool Unique() const;

		/// increment refcount by one
		void _AddRef();
		/// decrement refcount and destroy object if refcount is zero
		void _Release();

		void _Share();
	protected:
		/// destructor (called when refcount reaches zero)

		virtual ~SharedObject();
	private:
		volatile int mRefCount;
	};

	inline void SharedObject::_AddRef()
	{
		shh_assert(this->mRefCount >= 0);
		_Increment(this->mRefCount);
	}

	inline void SharedObject::_Release()
	{
		shh_assert(this->mRefCount > 0);

		if (0 == _Decrement(this->mRefCount))
		{
			shh_delete this;
		}    
	}

	inline void SharedObject::_Share()
	{
		shh_assert(this->mRefCount == Invalid_Count);
		_Exchange(this->mRefCount, (int)1);
	}

	inline bool SharedObject::Unique() const
	{
		return (this->mRefCount == 1);
	}

	inline bool SharedObject::Shared() const
	{
		return mRefCount != Invalid_Count;
	}

	inline int SharedObject::RefCount() const
	{
		return this->mRefCount;
	}
	
}

#endif //__SHARED_OBJECT_H__




    
    