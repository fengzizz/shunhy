#pragma once
#include "D3d11_Common.h"
#include "RenderFormat.h"
namespace Shh
{
	class D3d11Buffer : D3d11Resource
	{
	public:
		virtual ~D3d11Buffer();
		D3d11Buffer(ID3D11Buffer* buffer);
		virtual void Release();

		ID3D11Buffer* GetBuffer() const;
		bool IsValid() const;
	protected:
		ID3D11Buffer* mBuffer;
	};

	inline bool D3d11Buffer::IsValid() const
	{
		return NULL != mBuffer;
	}

	inline ID3D11Buffer* D3d11Buffer::GetBuffer() const
	{
		return mBuffer;
	}

}