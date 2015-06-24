


#ifndef __PixelFormat_H__
#define __PixelFormat_H__
#include "Core/TEnum.h"
#include "Core/U8String.h"
namespace Shh
{
	
	class PixelFormat//枚举值以DXGI_FORMAT为参考
	{
		__Declare_Enum
		{
			// color format
			UNKNOWN                      = 0,
			R32G32B32A32_TYPELESS        = 1,
			R32G32B32A32_FLOAT           = 2,
			R32G32B32A32_UINT            = 3,
			R32G32B32A32_SINT            = 4,
			R32G32B32_TYPELESS           = 5,
			R32G32B32_FLOAT              = 6,
			R32G32B32_UINT               = 7,
			R32G32B32_SINT               = 8,
			R16G16B16A16_TYPELESS        = 9,
			R16G16B16A16_FLOAT           = 10,
			R16G16B16A16_UNORM           = 11,
			R16G16B16A16_UINT            = 12,
			R16G16B16A16_SNORM           = 13,
			R16G16B16A16_SINT            = 14,
			R32G32_TYPELESS              = 15,
			R32G32_FLOAT                 = 16,
			R32G32_UINT                  = 17,
			R32G32_SINT                  = 18,
			R32G8X24_TYPELESS            = 19,
			D32_FLOAT_S8X24_UINT         = 20,
			R32_FLOAT_X8X24_TYPELESS     = 21,
			X32_TYPELESS_G8X24_UINT      = 22,
			R10G10B10A2_TYPELESS         = 23,
			R10G10B10A2_UNORM            = 24,
			R10G10B10A2_UINT             = 25,
			R11G11B10_FLOAT              = 26,
			R8G8B8A8_TYPELESS            = 27,
			R8G8B8A8_UNORM               = 28,
			R8G8B8A8_UNORM_SRGB          = 29,
			R8G8B8A8_UINT                = 30,
			R8G8B8A8_SNORM               = 31,
			R8G8B8A8_SINT                = 32,
			R16G16_TYPELESS              = 33,
			R16G16_FLOAT                 = 34,
			R16G16_UNORM                 = 35,
			R16G16_UINT                  = 36,
			R16G16_SNORM                 = 37,
			R16G16_SINT                  = 38,
			R32_TYPELESS                 = 39,
			D32_FLOAT                    = 40,
			R32_FLOAT                    = 41,
			R32_UINT                     = 42,
			R32_SINT                     = 43,
			R24G8_TYPELESS               = 44,
			D24_UNORM_S8_UINT            = 45,
			R24_UNORM_X8_TYPELESS        = 46,
			X24_TYPELESS_G8_UINT         = 47,
			R8G8_TYPELESS                = 48,
			R8G8_UNORM                   = 49,
			R8G8_UINT                    = 50,
			R8G8_SNORM                   = 51,
			R8G8_SINT                    = 52,
			R16_TYPELESS                 = 53,
			R16_FLOAT                    = 54,
			D16_UNORM                    = 55,
			R16_UNORM                    = 56,
			R16_UINT                     = 57,
			R16_SNORM                    = 58,
			R16_SINT                     = 59,
			R8_TYPELESS                  = 60,
			R8_UNORM                     = 61,
			R8_UINT                      = 62,
			R8_SNORM                     = 63,
			R8_SINT                      = 64,
			A8_UNORM                     = 65,
			R1_UNORM                     = 66,

			B8G8R8A8_UNORM				= 87,
			B8G8R8X8_UNORM				= 88,
			B8G8R8A8_TYPELESS            = 90,
			B8G8R8A8_UNORM_SRGB			= 91,
			B8G8R8X8_TYPELESS			= 92,
			B8G8R8X8_UNORM_SRGB			= 93,

			// end common   CommonCount

			//DXT FORMAT 

			BC1_TYPELESS                 = 70,
			BC1_UNORM                    = 71,
			BC1_UNORM_SRGB               = 72,
			BC2_TYPELESS                 = 73,
			BC2_UNORM                    = 74,
			BC2_UNORM_SRGB               = 75,
			BC3_TYPELESS                 = 76,
			BC3_UNORM                    = 77,
			BC3_UNORM_SRGB               = 78,
			BC4_TYPELESS                 = 79,
			BC4_UNORM                    = 80,
			BC4_SNORM                    = 81,
			BC5_TYPELESS                 = 82,
			BC5_UNORM                    = 83,
			BC5_SNORM                    = 84,

			BC6H_UF16                    = 95,
			BC6H_SF16                    = 96,
			BC7_TYPELESS                 = 97,
			BC7_UNORM                    = 98,
			BC7_UNORM_SRGB               = 99,

			// begin iPhone /  PowerVR
			PVRTC_RGB2 = 500,
			PVRTC_RGBA2,
			PVRTC_RGB4,
			PVRTC_RGBA4,
			// end iphone / PowerVR end   iOSCount

			//ETC
			ETC1_RGB8 = 700,

			//PF_NumPixelFormats,
			//PF_InvalidPixelFormat,
			//PF_DescPixelFormatsCount,	//	不调整NumPixelFormats和InvalidPixelFormat的顺序，以免引起BUG。用于像素格式描述的数组

			// 记录分块的标志位。 更改枚举之后，记得修改
			//CommonCount = D24S8 + 1, 
			//iOSCount = PVRTC_RGBA4 + 1,
		};
		__Declare_Enum_Struct(PixelFormat, 0);
	};

	 /** from Ogre
     * Flags defining some on/off properties of pixel formats
     */
    enum PixelFormatFlags {
        // This format has an alpha channel
        PFF_HASALPHA        = 0x00000001,      
        // This format is compressed. This invalidates the values in elemBytes,
        // elemBits and the bit counts as these might not be fixed in a compressed format.
        PFF_COMPRESSED    = 0x00000002,
        // This is a floating point format
        PFF_FLOAT           = 0x00000004,         
        // This is a depth format (for depth textures)
        PFF_DEPTH           = 0x00000008,
        // Format is in native endian. Generally true for the 16, 24 and 32 bits
        // formats which can be represented as machine integers.
        PFF_NATIVEENDIAN    = 0x00000010,
        // This is an intensity format instead of a RGB one. The luminance
        // replaces R,G and B. (but not A)
        PFF_LUMINANCE       = 0x00000020
    };

	/** From Ogre  Pixel component format */
	class PixelComponent
	{
		__Declare_Enum
		{
			Byte = 0,    /// Byte per component (8 bit fixed 0.0..1.0)
			Short = 1,   /// Short per component (16 bit fixed 0.0..1.0))
			Float16 = 2, /// 16 bit float per component
			Float32 = 3, /// 32 bit float per component
			COUNT = 4    /// Number of pixel types
		};
		__Declare_Enum_Struct(PixelComponent, 0);
	};
}







#endif // __PixelFormat_H__
