
#include "Core/CoreDef.h"
#include "PixelFormat.h"

namespace Shh
{

	//const PixelFormatDescription& getDescriptionFor(PixelFormat format)
	//{
	//	const int ord = (int)format;
	//	shh_assert( ord >= 0 && ord < PixelFormatConvert::DescPixelFormatsCount );
	//	return _pixelFormats[ord];
	//}
	//------------------------------------------------------------------------------
	/**
	Convert a pixel format string into a pixel format code.
	*/
	//PixelFormat
	//PixelFormatConvert::FromString(const U8String& str)
	//{
	//	for ( int i = 0; i < PixelFormatConvert::DescPixelFormatsCount; ++i )
	//	{
	//		const PixelFormatDescription& desc = getDescriptionFor( (PixelFormatConvert::PixelFormat)i );
	//		if ( str == desc.name )
	//		{
	//			return (PixelFormatConvert::PixelFormat)i;
	//		}
	//	}

	//	return PF_UNKNOWN;
	//}
	//------------------------------------------------------------------------

 //   unsigned int PixelFormatConvert::GetFlags( PixelFormat format )
	//{
	//	return getDescriptionFor(format).flags; 
	//}

	////------------------------------------------------------------------------
	//bool 
	//PixelFormatConvert::IsCompressed(PixelFormat code)
	//{
	//	return (GetFlags(code) & PFF_COMPRESSED) > 0;
	//}
	////------------------------------------------------------------------------
	//size_t 
	//PixelFormatConvert::GetNumElemBytes(PixelFormat code)
	//{
	//	 return getDescriptionFor(code).elemBytes;
	//}
	////------------------------------------------------------------------------
	//void 
	//PixelFormatConvert::GetBitMasks(PixelFormat format, uint32 rgba[4])
	//{
	//	const PixelFormatDescription &des = getDescriptionFor(format);
	//	rgba[0] = des.rmask;
	//	rgba[1] = des.gmask;
	//	rgba[2] = des.bmask;
	//	rgba[3] = des.amask;
	//}
	////------------------------------------------------------------------------
	//void 
	//PixelFormatConvert::GetBitDepths(PixelFormat format, int rgba[4])
	//{
	//	const PixelFormatDescription &des = getDescriptionFor(format);
	//	rgba[0] = des.rbits;
	//	rgba[1] = des.gbits;
	//	rgba[2] = des.bbits;
	//	rgba[3] = des.abits;
	//}

	////------------------------------------------------------------------------
	//size_t 
	//PixelFormatConvert::GetMemorySize(size_t width, size_t height, size_t depth, PixelFormat format)
	//{
	//	if(IsCompressed(format))
	//	{
	//		switch(format)
	//		{
	//			//  un compressed dxt
	//		case A8R8G8B8:
	//			return width*height*4;
	//		case R8G8B8:
	//			return width*height*3;
	//			// DXT formats work by dividing the image into 4x4 blocks, then encoding each
	//			// 4x4 block with a certain number of bytes. 
	//		case DXT1:
	//			return ((width+3)/4)*((height+3)/4)*8 * depth;
	//		case DXT2:
	//		case DXT3:
	//		case DXT4:
	//		case DXT5:
	//			return ((width+3)/4)*((height+3)/4)*16 * depth;

	//			// Size calculations from the PVRTC OpenGL extension spec
	//			// http://www.khronos.org/registry/gles/extensions/IMG/IMG_texture_compression_pvrtc.txt
	//			// Basically, 32 bytes is the minimum texture size.  Smaller textures are padded up to 32 bytes
	//		case PVRTC_RGB2:
	//		case PVRTC_RGBA2:
	//			shh_assert(depth == 1);
	//			return ( Math::n_max( width, 16 ) * Math::n_max( height, 8 ) * 2 + 7 ) / 8;
	//		case PVRTC_RGB4:
	//		case PVRTC_RGBA4:
	//			shh_assert(depth == 1);
	//			return (Math::n_max((int)width, 8) * Math::n_max((int)height, 8) * 4 + 7) / 8;
	//		case ETC1_RGB8:
	//			shh_assert(depth == 1);
	//			return ( 8 * ((width + 3) >> 2) * ((height + 3) >> 2) );
	//		default:
	//			n_error("PixelFormatConvert::GetMemorySize: Invalid compressed pixel format" );
	//			return 0;
	//		}
	//	}
	//	else
	//	{
	//		return width*height*depth*GetNumElemBytes(format);
	//	}
	//}	
	////------------------------------------------------------------------------------
	///**
	//Convert pixel format code into a string.
	//*/
	//U8String
	//PixelFormatConvert::ToString(PixelFormatConvert::PixelFormat code)
	//{
	//	return getDescriptionFor(code).name;
	//}
}
