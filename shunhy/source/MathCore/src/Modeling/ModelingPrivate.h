#ifndef __MODELING_PRIVATE_H__
#define __MODELING_PRIVATE_H__

namespace Shh
{
	namespace Modeling
	{

		inline void* _bias_in_bytes(void* ptr, size_t bias)
		{
			return reinterpret_cast<char*>(ptr) + bias;
		}

		template<typename _Myelem>
		class _elem_const_iterator
		{
		public:
			typedef _elem_const_iterator<_Myelem> self;
			typedef void* pointer;
			typedef char* byte_ptr;
			//typedef _vector_const_iterator self;
			_elem_const_iterator(pointer begin, size_t bias)
			{
				shh_assert(begin);
				this->_Ptr = begin;
				this->_Bias = bias;
			}
			const self& operator ++ () const
			{
				this->_BytePtr += this->_Bias;
				return *((self*)this);
			}
			const self& operator ++ (int) const
			{
				this->_BytePtr += this->_Bias;
				return *((self*)this);
			}
			void operator -- ()
			{
				this->_BytePtr -= this->_Bias;
			}
			const _Myelem& operator * () const
			{
				return *this->_Elem;
			}
			const _Myelem* operator -> () const
			{
				return this->_Elem;
			}

		protected:
			//void operator = (const self&);
			union
			{
				mutable byte_ptr _BytePtr;
				pointer _Ptr;
				_Myelem* _Elem;
			};
			size_t _Bias;
		private:
		};

		template<typename _Myelem>
		class _elem_iterator : public _elem_const_iterator<_Myelem>
		{
		public:
			typedef _elem_iterator<_Myelem> self;
			typedef _elem_const_iterator<_Myelem> super;
			_elem_iterator(pointer begin, size_t bias)
				: super(begin, bias)
			{
			}
			_Myelem& operator * ()
			{
				return *this->_Elem;
			}
			_Myelem* operator -> () const
			{
				return this->_Elem;
			}
			self& operator ++ () const
			{
				this->_BytePtr += this->_Bias;
				return *((self*)this);
			}
			const self& operator ++ (int) const
			{
				this->_BytePtr += this->_Bias;
				return *((self*)this);
			}
		};
	}
}
#endif //__MODELING_PRIVATE_H__