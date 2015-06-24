#ifndef __HARDWAREBUFFER_H__
#define __HARDWAREBUFFER_H__

#include "DrawDrv/RenderFormat.h"
#include "DrawDrv/RenderResource.h"

namespace Shh
{

	class _Shh_Export RenderBuffer : public RenderResource
	{
	public:
		RenderBuffer(SourceUsage usage, size_t strides, size_t count);
		virtual ~RenderBuffer() {}
		SourceUsage GetBufferUsage() const;
		size_t GetCount() const;
		size_t GetStrides() const;
	protected:
		SourceUsage mBufferUsage;
		size_t mCount;
		size_t mStrides;
	};
	inline RenderBuffer::RenderBuffer(SourceUsage usage, size_t strides, size_t count)
		:mBufferUsage(usage), mCount(count), mStrides(strides)
	{

	}
	inline SourceUsage RenderBuffer::GetBufferUsage() const
	{
		return mBufferUsage;
	}

	inline size_t RenderBuffer::GetStrides() const
	{
		return mStrides;
	}

	inline size_t RenderBuffer::GetCount() const
	{
		return mCount;
	}
}

#endif //__HARDWAREBUFFER_H__