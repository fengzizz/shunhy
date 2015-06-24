#ifndef __CORE_MEMORY_H__
#define __CORE_MEMORY_H__
#include "Core/CoreDef.h"
#include <memory>
namespace Shh
{
#define __copy_sizet__(_elem) ((size_t*)to)[_elem] = ((size_t*)from)[_elem]



#if _Shh_Platform_32Bits
#define __copy__32bits__(_elem) __copy_sizet__(_elem)
#elif _Shh_Platform_64Bits
#	define __copy__64bits__(_elem) __copy_sizet__(_elem)
#	define __copy__32bits__(_elem) ((uint32*)to)[_elem] = ((uint32*)from)[_elem]
#endif

#define DECL_ZERO(_Type, _Name) _Type _Name; Shh::Memory::Zero(&_Name, sizeof(_Name))

	class Memory
	{
	public:

		__forceinline static void* Copy(void* dest, const void* src, size_t count)
		{
			return ::memcpy(dest, src, count);
		}

		__forceinline static void* Set(void* dest, int val, size_t size)
		{
			return ::memset(dest, val, size);
		}
		__forceinline static void* Zero(void* dest, size_t size) 
		{
			return Set(dest, 0, size);
		}
	};

	class XMemory
	{
	public:
		__forceinline static void CopyN1(const void* from, void* to)
		{
			__copy__32bits__(0);
		}

		__forceinline static void CopyN2(const void* from, void* to)
		{
#if _Shh_Platform_32Bits
			__copy__32bits__(0);
			__copy__32bits__(1);
#elif _Shh_Platform_64Bits
			__copy__64bits__(0);
#endif
		}

		__forceinline static void CopyN3(const void* from, void* to)
		{
#if _Shh_Platform_32Bits
			__copy__32bits__(0);
			__copy__32bits__(1);
#elif _Shh_Platform_64Bits
			__copy__64bits__(0);
#endif	
			__copy__32bits__(2);
		}
		__forceinline static void CopyN4(const void* from, void* to)
		{
#if _Shh_Platform_32Bits
			__copy__32bits__(0);
			__copy__32bits__(1);
			__copy__32bits__(2);
			__copy__32bits__(3);
#elif _Shh_Platform_64Bits
			__copy__64bits__(0);
			__copy__64bits__(1);
#endif
		}

		__forceinline static void CopyN5(const void* from, void* to)
		{
#if _Shh_Platform_32Bits
			__copy__32bits__(0);
			__copy__32bits__(1);
			__copy__32bits__(2);
			__copy__32bits__(3);
#elif _Shh_Platform_64Bits
			__copy__64bits__(0);
			__copy__64bits__(1);
#endif
			__copy__32bits__(4);

		}

		__forceinline static void CopyN6(const void* from, void* to)
		{
#if _Shh_Platform_32Bits
			__copy__32bits__(0);
			__copy__32bits__(1);
			__copy__32bits__(2);
			__copy__32bits__(3);
			__copy__32bits__(4);
			__copy__32bits__(5);
#elif _Shh_Platform_64Bits
			__copy__64bits__(0);
			__copy__64bits__(1);
			__copy__64bits__(2);
#endif

		}

		__forceinline static void CopyN7(const void* from, void* to)
		{
#if _Shh_Platform_32Bits
			__copy__32bits__(0);
			__copy__32bits__(1);
			__copy__32bits__(2);
			__copy__32bits__(3);
			__copy__32bits__(4);
			__copy__32bits__(5);
#elif _Shh_Platform_64Bits
			__copy__64bits__(0);
			__copy__64bits__(1);
			__copy__64bits__(2);
#endif
			__copy__32bits__(6);
		}

		__forceinline static void CopyN8(const void* from, void* to)
		{
#if _Shh_Platform_32Bits
			__copy__32bits__(0);
			__copy__32bits__(1);
			__copy__32bits__(2);
			__copy__32bits__(3);
			__copy__32bits__(4);
			__copy__32bits__(5);
			__copy__32bits__(6);
			__copy__32bits__(7);
#elif _Shh_Platform_64Bits
			__copy__64bits__(0);
			__copy__64bits__(1);
			__copy__64bits__(2);
			__copy__64bits__(3);
#endif
		}

	private:

	};



	class _Shh_Export MemoryBlock final
	{
		__NoCopy(MemoryBlock);
	public:
		MemoryBlock();
		MemoryBlock(size_t size);
		~MemoryBlock();

		void Clear();
		void ResizeDiscard(size_t size);
		void ResizeDefault(size_t size, byte default_value);
		void Resize(size_t size);
		void Resize(size_t size, byte new_value);
		void Set(void* src, size_t begin, size_t len);
		size_t GetSize() const;
		void* GetPtr() const;
		void* GetPtr(int bias) const;
		template <typename T>
		T* As() const;

		template <typename T>
		T* As(int bias) const;
	private:

		void alloc(size_t size);
		void free();

		byte* mData;
		size_t mSize;
	};

	inline size_t MemoryBlock::GetSize() const
	{
		return mSize;
	}

	inline void* MemoryBlock::GetPtr() const
	{
		return mData;
	}

	inline void* MemoryBlock::GetPtr(int bias) const
	{
		return mData + bias;
	}

	template <typename T>
	inline T* MemoryBlock::As() const
	{
		return (T*)this->mData;
	}
	template <typename T>
	inline T* MemoryBlock::As(int bias) const
	{
		return (T*)(this->mData + bias);
	}
}

#endif //__CORE_MEMORY_H__