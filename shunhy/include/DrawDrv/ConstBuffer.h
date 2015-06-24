#ifndef __CONSTBUFFER_H__
#define __CONSTBUFFER_H__
#include "RenderFormat.h"
#include "MathCore/Matrix4.h"

namespace Shh
{
	struct CBufferCamera
	{
		Matrix4 View;
		Matrix4 Proj;
	};

	struct CBufferObject
	{
		Matrix4 World;
	};
}

#endif //__CONSTBUFFER_H__