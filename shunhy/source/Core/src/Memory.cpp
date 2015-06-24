#include "Memory.h"
#include "Debug.h"
namespace Shh
{
	MemoryBlock::MemoryBlock()
		:mData(nullptr)
		,mSize(0)
	{

	}

	MemoryBlock::~MemoryBlock()
	{
		free();
	}

	MemoryBlock::MemoryBlock(size_t size)
	{
		alloc(size);
	}

	void MemoryBlock::Clear()
	{
		free();
	}

	void MemoryBlock::Set(void* src, size_t begin, size_t len)
	{
		shh_assert(begin + len <= mSize);
		Memory::Copy(mData + begin, src, len);
	}

	void MemoryBlock::ResizeDiscard(size_t size)
	{
		const byte* old =  mData;
		size_t old_size = mSize;
		alloc(size);
		shh_delete [] old;
	}
	void MemoryBlock::ResizeDefault(size_t size, byte default_value)
	{
		const byte* old =  mData;
		size_t old_size = mSize;
		alloc(size);

		Memory::Set(mData, default_value, size);

		shh_delete [] old;
	}
	void MemoryBlock::Resize(size_t size)
	{
		const byte* old =  mData;
		size_t old_size = mSize;
		alloc(size);

		Memory::Copy(mData, old, (old_size < mSize) ? old_size : mSize);

		shh_delete [] old;
	}

	void MemoryBlock::Resize(size_t size, byte new_value)
	{
		size_t old = mSize;
		Resize(size);
		if (size > old)
		{
			Memory::Set(mData + old, new_value, size - old);
		}
	}

	void MemoryBlock::alloc(size_t size)
	{
		mData = shh_new byte[size];
		mSize = size;
	}

	void MemoryBlock::free()
	{
		shh_delete [] mData;
		mData = nullptr;
		mSize = 0;
	}

}