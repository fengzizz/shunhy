#ifndef __D3D11_UTILS_H__
#define __D3D11_UTILS_H__
#include "D3d11_Common.h"
namespace Shh
{


	namespace d3d11convert
	{
		DXGI_FORMAT to(const InputElementFormat& value);

		DXGI_FORMAT to(const IndexBufferFormat& value);

		const U8String& to(const ShaderSematic& value);

		inline D3D11_USAGE to(const SourceUsage& value)
		{
			return static_cast<D3D11_USAGE>(value.getEnum());
		}


	}
}
#endif //__D3D11_UTILS_H__


