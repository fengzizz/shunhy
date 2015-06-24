#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include "Graphics/GraphicSystem.h"
namespace Shh
{		
	typedef sptr<GraphicInstance> GraphicInstancePtr;
	typedef std::vector<GraphicInstancePtr> GraphicInstances;
	class _Shh_Export Graphics : public GraphicSystem 
	{
		__Dynamic_Alloc(Graphics);
	public:

		virtual DrawDrvCode GetDriverType() const;
		virtual GPUProgramHandle CreateGPUProgram(const U8String& name, const U8String& vs, const U8String& ps, OUT CompileMessageList& messageList);
		virtual PrimitiveHandle CreatePrimitive(const VertexBufferData& vbd, const IndexBufferData* ibd);

		virtual void SetGPUProgram(const GPUProgramHandle& handle);
		virtual void DrawPrimitive(const PrimitiveHandle& handle);

		Graphics();
		virtual ~Graphics();
		void Setup(size_t width, size_t height, size_t handle, bool fullScrean, DrawDrvCode type);
		void BeginScene();
		void EndScene();
		void Render(const RenderObjects& objects);
		void Destroy();
		Renderer* GetRender() const;

;

		const GraphicInstances& _GetGraphicResources() const;
	private:

		template<typename _Ty>
		_Ty* buildResource(RenderHandle& handle);
		void addResource(const GraphicInstancePtr& resource);
		void releaseResources();
		Renderer* mRenderer;
		GraphicInstances mGraphicInstances;
	};

	inline Renderer* Graphics::GetRender() const
	{
		return mRenderer;
	}

	inline const GraphicInstances& Graphics::_GetGraphicResources() const
	{
		return mGraphicInstances;
	}
}


#endif //__GRAPHICS_H__