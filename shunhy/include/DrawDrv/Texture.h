#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "DrawDrv/RenderFormat.h"
#include "DrawDrv/RenderResource.h"
namespace Shh
{
	class _Shh_Export Texture : public RenderResource
	{
	public:
		virtual TextureCode GetType() const = 0;
		virtual ~Texture(){}
	};
	class _Shh_Export Texture1D : public Texture
	{

	};
	class _Shh_Export Texture2D : public Texture
	{

	};
	class _Shh_Export TextureCube : public Texture
	{

	};
	class _Shh_Export Texture3D : public Texture
	{

	};
}

#endif //__TEXTURE_H__
