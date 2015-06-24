#ifndef __GRAPHIC_RENDERER_H__
#define __GRAPHIC_RENDERER_H__

#include "Graphics/GraphicsDef.h"
namespace Shh
{
	class GraphicRenderer
	{
	public:
		virtual ~GraphicRenderer();
		virtual void Render(Renderable* renderable) = 0;
	};

}


#endif //__GRAPHIC_RENDERER_H__
