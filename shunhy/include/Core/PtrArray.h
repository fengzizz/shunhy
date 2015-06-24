
#ifndef __PTR_ARRAY_H__
#define __PTR_ARRAY_H__
#include "Core/CoreDef.h"
namespace Shh
{
	template<typename _Ty>
	class _Shh_Export_Tmpl ptrarray final
	{
	public:		
		typedef _Ty* ptr_type;
		typedef std::vector<ptr_type> container;
		typedef typename container::size_type size_type;
		typedef typename container::iterator iterator;
		typedef typename container::const_iterator const_iterator;
		typedef typename container::reference reference;
		typedef typename container::const_reference const_reference;
		inline ptrarray()
		{

		}
		inline ~ptrarray()
		{
			clear();
		}

		template<typename _Sub>
		inline _Sub* push_back()
		{
			_Sub* sub = shh_new _Sub;
			_array.push_back(sub);
			return sub;
		}

		inline ptr_type push_back(ptr_type elem)
		{
			_array.push_back(elem);
			return elem;
		}

		inline const_reference back() const
		{
			return _array.back();
		}

		inline reference back()
		{
			return _array.back();
		}

		inline const_reference front() const
		{
			return _array.front();
		}

		inline reference front()
		{
			return _array.front();
		}

		inline void clear()
		{
			container::iterator it = _array.begin();
			container::iterator end = _array.end();
			while(it != end)
			{
				shh_delete (*it);
				++it;
			}
			_array.clear();		
		}

		inline iterator begin()
		{
			return _array.begin();
		}

		inline iterator end()
		{
			_array.end();
		}

		inline const_iterator begin() const
		{
			return _array.begin();
		}

		inline const_iterator end() const
		{
			return _array.end();
		}

		inline ptr_type operator[](size_type index) const
		{
			return _array[index];
		}

		inline size_type size() const
		{
			return _array.size();
		}
	private:
		container _array;

	private:
		ptrarray(ptrarray const &);
		ptrarray & operator=(ptrarray const &);
		void operator==( ptrarray const& ) const;
		void operator!=( ptrarray const& ) const;
	};

}

#endif //__PTR_ARRAY_H__