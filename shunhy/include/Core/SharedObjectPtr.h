
//from genesis-3d.
#ifndef __SPTR_H__
#define __SPTR_H__
#include "Core/CoreConfig.h"
//------------------------------------------------------------------------------
namespace Shh
{
	template<typename _Ty>
	class _Shh_Export_Tmpl sptr
	{
	public:
		/// constructor
		sptr();

		/// construct from smart pointer
		sptr(const sptr<_Ty>& p);

		/// construct from C++ pointer
		explicit sptr(_Ty* p);


		/// destructor
		~sptr();

		/// reset
		void reset(_Ty* rhs);
		void reset();
		/// assignment operator
		void operator=(const sptr<_Ty>& rhs);

		/// equality operator
		bool operator==(const sptr<_Ty>& rhs) const;
		/// inequality operator
		bool operator!=(const sptr<_Ty>& rhs) const;
		/// shortcut equality operator
		bool operator==(const _Ty* rhs) const;
		/// shortcut inequality operator
		bool operator!=(const _Ty* rhs) const;
		/// shortcut less operator
		bool operator<(const sptr<_Ty>& rhs) const;
		/// shortcut greator operator
		bool operator>(const sptr<_Ty>& rhs) const;
		/// safe -> operator
		_Ty* operator->() const;
		/// safe dereference operator
		_Ty& operator*() const;
		/// safe pointer cast operator
		operator _Ty*() const;

		/// cast
		template<typename OTHERTYPE> const sptr<OTHERTYPE>& cast() const;
		/// cast
		template<typename OTHERTYPE> sptr<OTHERTYPE> dynamiccast() const;
		/// check if pointer is valid
		bool isvalid() const;
		/// return direct pointer (asserts if null pointer)
		_Ty* get() const;

		void swap(sptr<_Ty>& other);

		static sptr<_Ty> null();

	private:
		_Ty* ptr;
	};

	template<typename _Ty>
	sptr<_Ty>::sptr() :
	ptr(0)
	{
		// empty
	}

	template<typename _Ty>
	sptr<_Ty>::sptr(_Ty* p) 
		: ptr(p)
	{
		if (0 != this->ptr)
		{
			if (Shh::Invalid_Count == this->ptr->RefCount())
				this->ptr->_Share();	
			else 
				this->ptr->_AddRef();
		}
	}

	template<typename _Ty>
	sptr<_Ty>::sptr(const sptr<_Ty>& p)
		:ptr(p.ptr)
	{
		if (0 != this->ptr)
		{
			this->ptr->_AddRef();
		}
	}

	template<typename _Ty>
	sptr<_Ty>::~sptr()
	{
		if (0 != this->ptr)
		{
			this->ptr->_Release();
			this->ptr = 0;
		}
	}

	template<typename _Ty>
	void sptr<_Ty>::operator=(const sptr<_Ty>& rhs)
	{
		if (this->ptr != rhs.ptr)
		{
			if (this->ptr)
			{
				this->ptr->_Release();
			}
			this->ptr = rhs.ptr;
			if (this->ptr)
			{
				this->ptr->_AddRef();
			}
		}
	}

	template<typename _Ty>
	void sptr<_Ty>::reset(_Ty* rhs)
	{
		if (this->ptr != rhs)
		{
			if (this->ptr)
			{
				this->ptr->_Release();
			}
			this->ptr = rhs;
			if (this->ptr)
			{
				if (Shh::Invalid_Count == this->ptr->RefCount())
					this->ptr->_Share();
				else
					this->ptr->_AddRef();
			}
		}
	}

	template<typename _Ty>
	void sptr<_Ty>::reset()
	{
		if (this->ptr)
		{
			this->ptr->_Release();
			this->ptr = 0;
		}
	}

	template<typename _Ty>
	bool sptr<_Ty>::operator==(const sptr<_Ty>& rhs) const
	{
		return (this->ptr == rhs.ptr);
	}

	template<typename _Ty>
	bool sptr<_Ty>::operator!=(const sptr<_Ty>& rhs) const
	{
		return (this->ptr != rhs.ptr);
	}

	template<typename _Ty>
	bool sptr<_Ty>::operator==(const _Ty* rhs) const
	{
		return (this->ptr == rhs);
	}

	template<typename _Ty>
	bool sptr<_Ty>::operator!=(const _Ty* rhs) const
	{
		return (this->ptr != rhs);
	}

	template<typename _Ty>
	bool sptr<_Ty>::operator<(const sptr<_Ty>& rhs) const
	{
		return (this->ptr < rhs.ptr);
	}

	template<typename _Ty>
	bool sptr<_Ty>::operator>(const sptr<_Ty>& rhs) const
	{
		return (this->ptr > rhs.ptr);
	}

	template<typename _Ty>
	_Ty* sptr<_Ty>::operator->() const
	{
		shh_assert2(this->ptr, "NULL pointer access in Ptr::operator->()!");
		return this->ptr;
	}

	template<typename _Ty>
	inline _Ty& sptr<_Ty>::operator*() const
	{
		shh_assert2(this->ptr, "NULL pointer access in Ptr::operator*()!");
		return *this->ptr;
	}

	template<typename _Ty>
	inline sptr<_Ty>::operator _Ty*() const
	{
		shh_assert2(this->ptr, "NULL pointer access in Ptr::operator TYPE*()!");
		return this->ptr;
	}

	template<typename _Ty>
	template<typename OTHERTYPE> 
	inline const sptr<OTHERTYPE>& sptr<_Ty>::cast() const
	{
		// note: this is an unsafe cast
		shh_assert2(nullptr != dynamic_cast<OTHERTYPE*>(this->ptr), "cannot cast.");
		return *reinterpret_cast<const sptr<OTHERTYPE>*>(this);
	}

	template<typename _Ty>
	template<typename OTHERTYPE> 
	inline sptr<OTHERTYPE> sptr<_Ty>::dynamiccast() const
	{
		sptr<OTHERTYPE> oth;
		oth.reset(dynamic_cast<OTHERTYPE*>(this->get()));
		return oth;
	}

	template<typename _Ty>
	inline bool sptr<_Ty>::isvalid() const
	{
		return (0 != this->ptr);
	}

	template<typename _Ty>
	inline _Ty* sptr<_Ty>::get() const
	{
		return this->ptr;
	}

	template<typename _Ty>
	void sptr<_Ty>::swap(sptr<_Ty>& other) 
	{
		_Ty* temp = other.ptr;
		other.ptr = this->ptr;
		this->ptr = temp;
	}


	template<typename _Ty>
	inline sptr<_Ty> sptr<_Ty>::null()
	{
		return sptr<_Ty>();
	}
}
#endif //__SPTR_H__
