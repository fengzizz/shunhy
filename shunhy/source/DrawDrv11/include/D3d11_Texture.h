#pragma once
#include "D3d11_Common.h"
#include "Texture.h"

namespace Shh
{
	class D3d11Texture : public Texture
	{
	public:
		D3d11Texture(ID3D11Resource* tex_resouce);
		virtual TextureCode GetType() const override;
		virtual void Release() override;
		virtual ~D3d11Texture();
	protected:
		TextureCode mType;
		union
		{
			ID3D11Resource* mResource;
			ID3D11Texture1D* mTex1D;
			ID3D11Texture2D* mTex2D;
			ID3D11Texture3D* mTex3D;
		};
		
	};
}