#pragma once
#include "VertexBuffer.h"
#include "D3d9_Common.h"
#include "D3d9_Buffer.h"
namespace Shh
{
	class D3d9VertexBuffer :  public D3d9Buffer, public VertexBuffer//
	{
	public: 
		D3d9VertexBuffer(IDirect3DVertexBuffer9* vertex_buffer, SourceUsage usage);
		virtual void Release() override;
		virtual ~D3d9VertexBuffer() override;
		virtual SourceUsage GetBufferUsage() const override;
		static void TransformUsage(SourceUsage buffer_usage, DWORD& vertex_usage, D3DPOOL& pool_type);
	protected:
		IDirect3DVertexBuffer9* mVertexBuffer;
	private:
		void _release();
	};
	inline void D3d9VertexBuffer::_release()
	{
		D3d9Common::DeleteCOMptr(mVertexBuffer);
	}
}