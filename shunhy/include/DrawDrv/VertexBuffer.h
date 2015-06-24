#ifndef __VERTEXBUFFER_H__
#define __VERTEXBUFFER_H__

#include "DrawDrv/RenderFormat.h"
#include "DrawDrv/RenderBuffer.h"
//
// 
//

namespace Shh
{
	class _Shh_Export VertexBuffer : public RenderBuffer
	{
		__Super(RenderBuffer);
	public:
		VertexBuffer(SourceUsage usage, size_t strides, size_t count);
		virtual ~VertexBuffer() {}
	};

	inline VertexBuffer::VertexBuffer(SourceUsage usage, size_t strides, size_t count)
		: super(usage, strides, count)
	{

	}
}
#endif //__VERTEXBUFFER_H__
