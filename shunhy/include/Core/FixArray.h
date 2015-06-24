
#ifndef __FIX_ARRAY_H__
#define __FIX_ARRAY_H__
#include "Core/Memory.h"
namespace Shh
{
	template<typename _Ty>
	class fixarray
	{
	public:
		typedef size_t size_type;
		typedef _Ty value_type;
		typedef _Ty* value_ptr;
		typedef value_ptr iterator;
		typedef const iterator const_iterator;
		typedef value_type& reference;
		typedef const reference const_reference;
		fixarray();
		fixarray(size_type count);	
		fixarray(size_type count, const value_type& default);	
		~fixarray();
		value_type& push_back();
		void push_back(const value_type& value);	

		const_reference back() const;
		reference back();
		const_reference front() const;
		reference front();

		void pop();
		void clear();
		void clear_with_buffer();

		size_type size() const;
		void reserve(size_type count);
		void resize(size_type size);

		iterator begin();
		iterator end();
		value_ptr get() const;
		const_iterator begin() const;
		const_iterator end() const;
		value_type& operator[](size_type index) const;
	protected:
		void _grow();
		void _free();
		void _alloc(size_type s);

		value_type* _elements;
		size_type _size;
		size_type _capacity;
	private:
		static const size_type MinGrowSize = 16;
		static const size_type MaxGrowSize = 65536; // FIXME: big grow size needed for mesh tools


		fixarray(fixarray const &);
		fixarray & operator=(fixarray const &);
		void operator==( fixarray const& ) const;
		void operator!=( fixarray const& ) const;
	};

	template<typename _Ty>
	fixarray<_Ty>::fixarray()
		: _size(0)
		, _capacity(0)
		, _elements(NULL)
	{
	}
	template<typename _Ty>
	fixarray<_Ty>::fixarray(size_type count)
		: _size(0)
		, _elements(NULL) 
	{
		_alloc(count);
		this->_size = count;
	}

	template<typename _Ty>
	fixarray<_Ty>::fixarray(size_type count, const value_type& default)
		: _size(0)
		, _elements(NULL) 
	{
		_alloc(count);
		this->_size = count;

		iterator it = this->begin();
		while(it != this->end())
		{
			*it = default;
			++it;
		}
	}

	template<typename _Ty>
	fixarray<_Ty>::~fixarray()
	{
		this->_free();
		this->_size = 0;
	}

	template<typename _Ty>
	void fixarray<_Ty>::clear()
	{
		this->_size = 0;
	}

	template<typename _Ty>
	void fixarray<_Ty>::clear_with_buffer()
	{
		this->_free();
		this->_size = 0;
	}

	template<typename _Ty>
	typename
	fixarray<_Ty>::size_type fixarray<_Ty>::size() const
	{
		return this->_size;
	}

	template<typename _Ty>
	typename 
	fixarray<_Ty>::value_type& fixarray<_Ty>::push_back()
	{
		if (this->_size >= this->_capacity)
		{
			this->_grow();
		}
		size_type index = this->_size;
		++(this->_size);
		return this->_elements[index];
	}

	template<typename _Ty>
	void fixarray<_Ty>::push_back(const value_type& value)
	{
		if (this->_size >= this->_capacity)
		{
			_grow();
		}
		this->_elements[this->_size] = value;
		++(this->_size);
	}
	template<typename _Ty>	
	void fixarray<_Ty>::pop()
	{
		shh_assert(0 < this->_size);
		--this->_size;
	}

	template<class _Ty>
	void fixarray<_Ty>::reserve(size_type count)
	{
		// allocate new array and copy over old elements
		_Ty* newElements = 0;
		if (count > 0)
		{
			newElements = shh_new _Ty[count];
			size_type numCopy = (this->_size < count) ? this->_size : count;
			Memory::Copy(this->_elements, newElements, numCopy * sizeof(_Ty));
		}

		// delete old elements
		this->_free();

		// set content to new elements
		this->_elements = newElements;
		this->_capacity = count;
	}
	template<class _Ty>
	void fixarray<_Ty>::resize(size_type size)
	{
		if (this->_capacity < size)
		{
			reserve(size);
		}
		this->_size = size;
	}
	template<typename _Ty>
	void fixarray<_Ty>::_grow()
	{			
		size_type growBy = _capacity >> 1;
		if (0 == growBy)
		{
			growBy = MinGrowSize;
		}
		else if (growBy > MaxGrowSize)
		{
			growBy = MaxGrowSize;
		}
		reserve(growBy + _capacity);
	}

	template<class _Ty> 
	void fixarray<_Ty>::_free()
	{
		if (this->_elements)
		{
			shh_delete this->_elements;
			this->_elements = NULL;
		}
		this->_capacity = 0;
	}

	template<class _Ty> 
	void fixarray<_Ty>::_alloc(size_type s)
	{
		shh_assert(0 == this->_elements);
		if (s > 0)
		{
			this->_elements = shh_new _Ty[s];
		}
		this->_capacity = s;
	}

	template<typename _Ty>
	typename 
		fixarray<_Ty>::iterator fixarray<_Ty>::begin()
	{
		return _elements;
	}
	template<typename _Ty>
	typename 
		fixarray<_Ty>::iterator fixarray<_Ty>::end()
	{
		return _elements + this->_size;
	}

	template<typename _Ty>
	typename 
		fixarray<_Ty>::const_reference fixarray<_Ty>::back() const
	{
		return (*(this->end() - 1));
	}
	template<typename _Ty>
	typename 
		fixarray<_Ty>::reference fixarray<_Ty>::back()
	{
		return (*(this->end() - 1));
	}

	template<typename _Ty>
	typename 
		fixarray<_Ty>::const_reference fixarray<_Ty>::front() const
	{
		return (*(this->begin()));
	}
	template<typename _Ty>
	typename 
		fixarray<_Ty>::reference fixarray<_Ty>::front()
	{
		return (*(this->begin()));
	}

	template<typename _Ty>
	typename 
		fixarray<_Ty>::value_ptr fixarray<_Ty>::get() const
	{
		return _elements;
	}

	template<typename _Ty>
	typename 
		fixarray<_Ty>::const_iterator fixarray<_Ty>::begin() const
	{
		return _elements;
	}
	template<typename _Ty>
	typename 
		fixarray<_Ty>::const_iterator fixarray<_Ty>::end() const
	{
		return _elements + this->_size;
	}
	template<typename _Ty>

	_Ty& fixarray<_Ty>::operator[](size_type index) const
	{
		return _elements[index];
	}
}


#endif //__FIX_ARRAY_H__