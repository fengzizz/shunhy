/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/


#include "PixelFormatDesc.h"

namespace Shh
{

	PixelFormatDescription g_pixelFormats[] = {
		//------------------------------------------------------------------------
		{"R8G8B8A8", PixelFormat::R8G8B8A8_UNORM,
		/* Bytes per element */
		4,
		/* Flags */
		PFF_HASALPHA | PFF_NATIVEENDIAN,
		/* Component type and count */
		PixelComponent::Byte, 4,
		/* rbits, gbits, bbits, abits */
		8, 8, 8, 8,
		/* Masks and shifts */
		0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF,
		24, 16, 8, 0
		},
		//------------------------------------------------------------------------
		{"BC1_UNORM", PixelFormat::BC1_UNORM,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PixelComponent::Byte, 3, // No alpha
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"BC2_UNORM", PixelFormat::BC2_UNORM,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PixelComponent::Byte, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"BC3_UNORM", PixelFormat::BC3_UNORM,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PixelComponent::Byte, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"BC4_UNORM", PixelFormat::BC4_UNORM,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PixelComponent::Byte, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"BC5_UNORM", PixelFormat::BC5_UNORM,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PixelComponent::Byte, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"R8_UNORM", PixelFormat::R8_UNORM,
		/* Bytes per element */
		1,
		/* Flags */
		PFF_LUMINANCE | PFF_NATIVEENDIAN,
		/* Component type and count */
		PixelComponent::Byte, 1,
		/* rbits, gbits, bbits, abits */
		8, 0, 0, 0,
		/* Masks and shifts */
		0xFF, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"R8G8_UNORM", PixelFormat::R8G8_UNORM,					
		/* Bytes per element */
		2,
		/* Flags */
		PFF_HASALPHA | PFF_LUMINANCE,
		/* Component type and count */
		PixelComponent::Byte, 2,
		/* rbits, gbits, bbits, abits */
		8, 0, 0, 8,
		/* Masks and shifts */
		0,0,0,0,0,0,0,0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGB2", PixelFormat::PVRTC_RGB2,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PixelComponent::Byte, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGBA2", PixelFormat::PVRTC_RGBA2,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PixelComponent::Byte, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGB4", PixelFormat::PVRTC_RGB4,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PixelComponent::Byte, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"PVRTC_RGBA4", PixelFormat::PVRTC_RGBA4,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED | PFF_HASALPHA,
		/* Component type and count */
		PixelComponent::Byte, 4,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
		//------------------------------------------------------------------------
		{"ETC1_RGB8", PixelFormat::ETC1_RGB8,
		/* Bytes per element */
		0,
		/* Flags */
		PFF_COMPRESSED,
		/* Component type and count */
		PixelComponent::Byte, 3,
		/* rbits, gbits, bbits, abits */
		0, 0, 0, 0,
		/* Masks and shifts */
		0, 0, 0, 0, 0, 0, 0, 0
		},
	};
}

