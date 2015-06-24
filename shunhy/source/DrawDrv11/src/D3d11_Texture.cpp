#include "D3d11_Texture.h"
#if __Renderer_d3d11__
namespace Shh
{
	D3d11Texture::D3d11Texture(ID3D11Resource* tex_resouce)
	{
		mResource = tex_resouce;
		D3D11_RESOURCE_DIMENSION type;
		mResource->GetType(&type);
		mType = (TextureCode)type;
		if(D3D11_RESOURCE_DIMENSION_TEXTURE2D == type)
		{
			D3D11_TEXTURE2D_DESC desc;
			mTex2D->GetDesc(&desc);
			if (6 == desc.ArraySize)
			{
				mType = RT_TEXCUBE;
			}
		}
	}

	D3d11Texture::~D3d11Texture()
	{

	}

	TextureCode D3d11Texture::GetType() const
	{
		return RT_UNKNOWN;
	}
	void D3d11Texture::Release()
	{
		D3d11Common::DeleteCOMptr(mResource);
	}
}
#endif
