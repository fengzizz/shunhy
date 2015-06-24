#pragma once
#include "DrawDrv/ResourceFactory.h"
#include "DrawDrv/ConstBuffer.h"
//
// 对外图形设备接口
//

//using namespace shh;

namespace Shh
{


	class _Shh_Export RenderDriver : public IRelease//_Shh_Export
	{
	public:
		virtual ~RenderDriver();
		virtual bool Initialize() = 0;

		virtual void SetShaderProgram(GPUProgram* program) = 0;

		virtual void DrawBegin() = 0;
		virtual void Draw(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, InputLayout* layout) = 0;
		virtual void DrawEnd() = 0;
		virtual void Release() = 0;
		virtual DrawDrvCode GetDrawDrvType() = 0;
		virtual ResourceFactory* GetResourceFactory() const = 0;
		virtual void UpdateConstBuffer_Camera(const CBufferCamera& buffer) = 0;
		virtual void UpdateConstBuffer_Object(const CBufferObject& buffer) = 0;
	protected:
		template<typename _Ty, typename _Ory>
		_Ty* convert(_Ory* ory)
		{
			return static_cast<_Ty*>(ory);
		}
		RenderDriver();
	};
	extern "C"{
		_Shh_Export RenderDriver* g_CreateRenderDevice(const DRV_DESC& desc);
		_Shh_Export void g_RecycleRenderDevice(RenderDriver* instance);
	}
	typedef RenderDriver* (* createDrvFunc)(const DRV_DESC& desc);
	typedef void (* recycleDrvFunc)(RenderDriver* instance);
}//    ShhCALLCONV
