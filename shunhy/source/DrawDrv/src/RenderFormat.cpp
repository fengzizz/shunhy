#include "RenderFormat.h"

namespace Shh
{
	size_t IndexBufferFormat::getSize(const IndexBufferFormat& format)
	{
		size_t size = 0;
		switch(format._enum)
		{
		case IndexBufferFormat::Index16:
			{
				size = 2; 
				break;
			}
		case IndexBufferFormat::Index32:
			{
				size = 4;
				break;
			}
		default:
			break;
		}
		return size;
	}

	size_t IndexBufferFormat::getIndexCount(const IndexBufferFormat& format, size_t sizeInBytes)
	{
		switch(format._enum)
		{
		case IndexBufferFormat::Index16:
			{
				return sizeInBytes / 2;
			}
		case IndexBufferFormat::Index32:
			{
				return sizeInBytes / 4;
			}
		default:
			{
				break;
			}
		}
		return 0;
	}

	size_t InputElementFormat::getSize(const InputElementFormat& format)
	{
		switch (format.getEnum())
		{
		case Float:     return 4;
		case Float2:    return 8;
		case Float3:    return 12;
		case Float4:    return 16;
		case UByte4:    return 4;
		case Short2:    return 4;
		case Short4:    return 8;
		case ColorBGRA: return 4;
		case ColorRGBA: return 4;

		default:
			break;
		}
		return 0;
	}
}