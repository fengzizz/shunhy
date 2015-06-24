
#include "Core/SharedObject.h"
#include "DrawDrv/InputLayout.h"
#include "Renderer/Renderer.h"
#include "Graphics/SceneObject.h"
#include "Graphics/Renderable.h"
#include "Graphics/GraphicRenderer.h"
#include "GraphicInstance.h"
#include "Graphics.h"
//#include "Graphics/Scene.h"
//#include "Graphics/SceneSystem.h"
namespace Shh
{
	//void SceneSystem::Add(const sptr<Scene>& scene)
	//{
	//	mScenes.push_back(scene);
	//}
	class GraphicResourceTool
	{
	public:
		template<typename _Ty>
		static void Build(RenderHandle& handle, _Ty** ptr)
		{
			shh_assert(handle.IsNull());
			_Ty* resource = shh_new _Ty();

			*ptr = resource;
			//handle.mCode = _Ty::Code;
			handle.mResource = resource;
		}

		template<typename _Ty>
		static _Ty* Reflect(const RenderHandle& handle)
		{
			GraphicInstance* instance = handle.mResource;
			if (nullptr != instance)
			{
				if (_Ty::Code == instance->GetCode())
				{
					return static_cast<_Ty*>(instance);
				}
			}
			return nullptr;
		}

	};


	Graphics::Graphics()
		:mRenderer(nullptr)
	{

	}

	Graphics::~Graphics()
	{
		shh_delete mRenderer;
	}
	void Graphics::BeginScene()
	{
		shh_assert(mRenderer);
		mRenderer->BeginScene();
	}
	void Graphics::EndScene()
	{
		shh_assert(mRenderer);
		mRenderer->EndScene();
	}
	void Graphics::Destroy()
	{
		mRenderer->Destroy();
	}
	DrawDrvCode Graphics::GetDriverType() const
	{
		return mRenderer->GetDriverType();
	}
	void Graphics::Setup(size_t width, size_t height, size_t handle, bool fullScrean, DrawDrvCode type)
	{
		shh_assert(nullptr == mRenderer);
		mRenderer = shh_new Renderer();
		mRenderer->Setup(width, height, handle, fullScrean, type);
		mGraphicInstances.reserve(1000);
	}

	void Graphics::addResource(const GraphicInstancePtr& resource)
	{
		mGraphicInstances.push_back(resource);
	}

	template<typename _Ty>
	_Ty* Graphics::buildResource(RenderHandle& handle)
	{
		_Ty* resource;
		GraphicResourceTool::Build(handle, &resource);
		GraphicInstancePtr sr(resource);
		addResource(sr);
		return resource;
	}
	

	GPUProgramHandle Graphics::CreateGPUProgram(const U8String& name, const U8String& vs, const U8String& ps, OUT CompileMessageList& messageList)
	{
		GPUProgram* program = nullptr;
		mRenderer->GetResourceFactory()->CreateGPUProgram(name, vs, ps, &program, messageList); 

		RenderHandle handle;

		if (nullptr != program)
		{
			ShaderInstance* resource = buildResource<ShaderInstance>(handle);
			resource->SetResource(program);
		}
		return handle;
	}

	PrimitiveHandle Graphics::CreatePrimitive(const VertexBufferData& vbd, const IndexBufferData* ibd)
	{
		VertexBuffer* vb = nullptr;
		IndexBuffer* ib = nullptr;
		InputLayout* il = nullptr;
		mRenderer->GetResourceFactory()->CreateVertexBuffer(vbd, &vb);
		mRenderer->GetResourceFactory()->CreateInputLayout(vbd.vertex.vertexComponents, nullptr, 0, &il);

		if (ibd)
		{
			mRenderer->GetResourceFactory()->CreateIndexBuffer(*ibd, &ib);
		}

		RenderHandle handle;
		if (nullptr != vb)
		{
			PrimitiveInstance* primitive = buildResource<PrimitiveInstance>(handle);
			primitive->SetResource(vb);
			primitive->SetIndexBuffer(ib);
			primitive->SetInputLayout(il);
			primitive->SetPrimitiveTopology(vbd.topology);
		}
		return handle;
	}


	//struct Vertex
	//{
	//	Vector3 position;
	//};

	//static VertexBuffer* test_vb = nullptr;
	//static IndexBuffer* test_ib = nullptr;
	//static InputLayout* test_il = nullptr;
	//static GPUProgram* test_gp = nullptr;

	//bool initTest(Graphics* gr, const GraphicResources& grs)
	//{
	//	shh_log("------------------ render test -------------------");
	//	Renderer* renderer = gr->GetRender();
	//	ResourceFactory* factory = renderer->GetResourceFactory();

	//	Vertex vertices[4];

	//	vertices[0].position = Vector3(-0.5f,  0.5f, 0.5f);
	//	vertices[1].position = Vector3( 0.5f,  0.5f, 0.5f);
	//	vertices[2].position = Vector3(-0.5f, -0.5f, 0.5f);
	//	vertices[3].position = Vector3( 0.5f, -0.5f, 0.5f);

	//	uint16 indices[] = {0,1,3,0,3,2};
	//	InputElements elements;
	//	elements.push_back(InputElement(ShaderSematic::POSITION, 0, PixelFormat::R32G32B32_FLOAT, 0, 0, ILT_VERTEX_DATA));

	//	factory->CreateVertexBuffer(&vertices[0], sizeof(Vector3), 4, SourceUsage::Default, &test_vb);
	//	factory->CreateIndexBuffer(&indices[0], IndexBufferFormat::Index16, 6, SourceUsage::Default, &test_ib);
	//	factory->CreateInputLayout(elements, NULL, 0, &test_il);

	//	//for(GraphicResources::const_iterator it = grs.begin(); it != grs.end(); ++it)
	//	//{
	//	//	sptr<ShaderResource> sr = it->dynamiccast<ShaderResource>();
	//	//	if (sr.isvalid())
	//	//	{
	//	//		test_gp = sr->GetResource();
	//	//	}
	//	//}

	//	SSTREAM_COUT(shader)
	//		<<"float4 VSMain(float3 pos : POSITION) : SV_POSITION \r\n"
	//		<<"{ \r\n"
	//		<<"		return float4(pos, 1); \r\n"
	//		<<"} \r\n"
	//		<<"float4 PSMain():SV_TARGET \r\n"
	//		<<"{ \r\n"
	//		<<"  return float4(1,1,1,1); \r\n"
	//		<<"} \r\n";
	//	String ts = shader.str();
	//	CompileMessageList messageList;
	//	renderer->GetResourceFactory()->CreateGPUProgram("test_program", ts, ts, &test_gp, messageList); 
	//	return true;
	//}

	//void renderTest(Renderer* renderer)
	//{
	//	renderer->SetShaderProgram(test_gp);
	//	renderer->Draw(test_vb, test_ib, test_il);
	//}

	void Graphics::SetGPUProgram(const GPUProgramHandle& handle)
	{
		ShaderInstance* instance = GraphicResourceTool::Reflect<ShaderInstance>(handle);
		if (nullptr != instance)
		{
			GPUProgram* resource = instance->GetResource();

			mRenderer->SetShaderProgram(resource);	
		}
	}
	void Graphics::DrawPrimitive(const PrimitiveHandle& handle)
	{
		PrimitiveInstance* instance = GraphicResourceTool::Reflect<PrimitiveInstance>(handle);
		if (nullptr != instance)
		{
			VertexBuffer* resource = instance->GetResource();
			IndexBuffer* indices = instance->GetIndexBuffer();
			InputLayout* layout = instance->GetInputLayout();
			mRenderer->Draw(resource, indices, layout);
		}
	}

	void Graphics::Render(const RenderObjects& objects)
	{
		Renderables drawList;
		__for_each(RenderObjects, objects, it)
		{
			(*it)->PushTo(drawList);
		}

		__for_each(Renderables, drawList, it)
		{
			(*it)->GetSceneObject()->GetRenderer()->Render(*it);
		}

		////
		//static bool init = initTest(this, mGraphicResources);
		//if (init)
		//{
		//	renderTest(mRenderer);
		//}
	}
}