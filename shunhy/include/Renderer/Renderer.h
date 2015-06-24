#ifndef __RENDERER_H__
#define __RENDERER_H__
#include "DrawDrv/ConstBuffer.h"
#include "DrawDrv/RenderDriver.h"
#include "RendererDef.h"


namespace Shh
{
	class _Shh_Export Renderer final
	{
	public:
		Renderer();
		~Renderer();
		void Setup(size_t width, size_t height, size_t handle, bool fullScrean, DrawDrvCode type);

		void SetShaderProgram(GPUProgram* program);
		void BeginScene();
		void Draw(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer, InputLayout* layout);
		void EndScene();
		void Destroy();
		DrawDrvCode GetDriverType() const;
		ResourceFactory* GetResourceFactory() const;

		STRUCT_DATA_SET(CBufferCamera, Matrix4, View)
		STRUCT_DATA_SET(CBufferCamera, Matrix4, Proj)
		STRUCT_DATA_SET(CBufferObject, Matrix4, World)
	private:		
		RenderDriver* mDriver;
		CBufferCamera mCBufferCamera;
		CBufferObject mCBufferObject;
	};

	inline ResourceFactory* Renderer::GetResourceFactory() const
	{
		shh_assert(mDriver);
		return mDriver->GetResourceFactory();
	}

	inline DrawDrvCode Renderer::GetDriverType() const
	{
		return mDriver->GetDrawDrvType();
	}
}


#endif //__RENDERER_H__