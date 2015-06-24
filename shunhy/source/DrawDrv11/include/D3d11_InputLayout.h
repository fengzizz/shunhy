#pragma once
#include "D3d11_Common.h"
#include "InputLayout.h"
#include "Core/U8String.h"
namespace Shh
{

	class D3d11InputLayout : public InputLayout, public D3d11Resource
	{
		__Super(InputLayout);
	public:
		virtual bool Valid() const;
		D3d11InputLayout(const InputLayout::InputElements& elems, ID3D11InputLayout* layout, D3d11Driver* driver);
		virtual ~D3d11InputLayout();
		virtual void Release();
		ID3D11InputLayout* GetLayout() const;
		static void TransInputElement(const InputElement& src, D3D11_INPUT_ELEMENT_DESC& dest);
	protected:
		ID3D11InputLayout* mLayout;
	};

	inline ID3D11InputLayout* D3d11InputLayout::GetLayout() const
	{
		return mLayout;
	}
}