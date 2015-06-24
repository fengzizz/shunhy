#pragma once
#include "D3d9_Common.h"
#include "D3d9_Buffer.h"
#include "IndexBuffer.h"
namespace Shh
{
	class D3d9IndexBuffer : public IndexBuffer, public D3d9Buffer
	{
	public: 
		D3d9IndexBuffer(IDirect3DIndexBuffer9* buffer, SourceUsage usage, IndexBufferFormat index_format);
		virtual void Release() override;
		virtual ~D3d9IndexBuffer();
		virtual SourceUsage GetBufferUsage() const override;
		virtual IndexBufferFormat GetIndexBufferFormat() const override;
		static void TransformUsage(SourceUsage buffer_usage, DWORD& index_usage, D3DPOOL& pool_type);
	protected:
		IDirect3DIndexBuffer9* mIndexBuffer;
	private:
		void _release();
	};
	inline void D3d9IndexBuffer::_release()
	{
		D3d9Common::DeleteCOMptr(mIndexBuffer);
	}
}