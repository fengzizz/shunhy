#ifndef __GRAPHIC_SYSTEM_H__
#define __GRAPHIC_SYSTEM_H__
#include "Core/Singleton.h"
#include "DrawDrv/RenderData.h"
#include "Renderer/RendererDef.h"
#include "Graphics/GraphicsDef.h"
#include "Graphics/RenderHandle.h"

namespace Shh
{		
	class _Shh_Export GraphicSystem : public Singleton<GraphicSystem>
	{
	public:
		virtual ~GraphicSystem();
		virtual DrawDrvCode GetDriverType() const = 0;
		virtual GPUProgramHandle CreateGPUProgram(const U8String& name, const U8String& vs, const U8String& ps, OUT CompileMessageList& messageList) = 0;
		virtual PrimitiveHandle CreatePrimitive(const VertexBufferData& vbd, const IndexBufferData* ibd) = 0;

		virtual void DrawPrimitive(const PrimitiveHandle& handle) = 0;
		virtual void SetGPUProgram(const GPUProgramHandle& handle) = 0;

	};

}


#endif //__GRAPHIC_SYSTEM_H__