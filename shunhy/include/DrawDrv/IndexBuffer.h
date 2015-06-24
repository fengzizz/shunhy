#ifndef __INDEXBUFFER_H__
#define __INDEXBUFFER_H__

#include "DrawDrv/RenderFormat.h"
#include "DrawDrv/RenderBuffer.h"
//

namespace Shh
{

	class _Shh_Export IndexBuffer : public RenderBuffer
	{
		__Super(RenderBuffer);
	public:
		IndexBuffer(SourceUsage usage, size_t strides, size_t count);
		virtual ~IndexBuffer(){}
		IndexBufferFormat GetFormat() const;
	protected:
		IndexBufferFormat mFormat;
	};

	inline IndexBuffer::IndexBuffer(SourceUsage usage, size_t strides, size_t count)
		: super(usage, strides, count)
	{

	}

	inline IndexBufferFormat IndexBuffer::GetFormat() const
	{
		return mFormat;
	}
}
#endif //__INDEXBUFFER_H__
