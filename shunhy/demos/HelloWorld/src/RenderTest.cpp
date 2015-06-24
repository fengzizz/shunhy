#include "Core/Log.h"
#include "Graphics/RenderHandle.h"
#include "Graphics/GraphicRenderer.h"
#include "Graphics/SceneObject.h"
#include "Graphics/Renderable.h"
#include "Graphics/Scene.h"
#include "Graphics/SceneSystem.h"
#include "Graphics/GraphicSystem.h"
#include "RenderTest.h"

namespace Shh
{

}


using namespace Shh;

namespace test
{

	class SimpleSceneObject;
	class SimpleRenderer;
	class SimpleRenderable;

	static SimpleSceneObject* gSceneObject = nullptr;
	static SimpleRenderer* gRenderer = nullptr;
	static SimpleRenderable* gRenderable = nullptr;
	static sptr<SimpleScene> gScene;
	static PrimitiveHandle gPrimitive;
	static GPUProgramHandle gShader;

	struct Vertex
	{
		Vector3 position;
	};


	class SimpleRenderer : public GraphicRenderer
	{
	public:
		virtual void Render(Renderable* renderable)
		{
			GraphicSystem* gs = GraphicSystem::GetSingletonPtr();
			gs->SetGPUProgram(gShader);
			gs->DrawPrimitive(gPrimitive);
		}
	};


	class SimpleSceneObject : public SceneObject
	{
	public:
		SimpleSceneObject()
		{
			setRenderer(gRenderer);
		}
		void SceneObject::PushTo(Renderables& list);
	};
	class SimpleRenderable : public Renderable
	{
	public:
		SimpleRenderable();
	};
	SimpleRenderable::SimpleRenderable()
	{
		setSceneObject(gSceneObject);
	}

	void SimpleSceneObject::PushTo(Renderables& list)
	{
		list.push_back(gRenderable);
	}



	void initRenderTest()
	{		
		shh_log("------------------ render test init -------------------");
		gRenderer = new SimpleRenderer();
		gSceneObject = new SimpleSceneObject();	
		gRenderable = new SimpleRenderable();

		gScene.reset(new SimpleScene());

		gScene->Add(gSceneObject);
		sptr<Scene> sp = gScene.cast<Scene>();
		SceneSystem::GetSingletonPtr()->Add(sp);

		static const size_t vertexCount = 4;
		static const size_t indexCount = 6;
		GraphicSystem* gs = GraphicSystem::GetSingletonPtr();

		Vertex vertices[vertexCount];
		vertices[0].position = Vector3(-0.5f,  0.5f, 0.5f);
		vertices[1].position = Vector3( 0.5f,  0.5f, 0.5f);
		vertices[2].position = Vector3(-0.5f, -0.5f, 0.5f);
		vertices[3].position = Vector3( 0.5f, -0.5f, 0.5f);
		uint16 indices[indexCount] = {0,1,3,0,3,2};

		VertexBufferData vbd;
		vbd.topology = PrimitieTopology::TriangleList;
		vbd.usage = SourceUsage::Default;
		vbd.vertexCount = vertexCount;

		vbd.vertex.vertexComponents.push_back(InputElement(ShaderSematic::POSITION, 0, InputElementFormat::Float3, 0, 0));

		VertexStream vstream;
		vstream.data = vertices;
		vstream.elemSizeInByte = sizeof(Vertex);
		vstream.offsetInByte = 0;

		vbd.vertex.vertexComponentStreams.push_back(vstream);

		IndexBufferData ibd;
		ibd.format = IndexBufferFormat::Index16;
		ibd.usage = SourceUsage::Default;
		ibd.indexCount = indexCount;
		ibd.stream = indices;

		gPrimitive = gs->CreatePrimitive(vbd, &ibd);

		SSTREAM_COUT(shader)
			<<"float4 VSMain(float3 pos : POSITION) : SV_POSITION \r\n"
			<<"{ \r\n"
			<<"		return float4(pos, 1); \r\n"
			<<"} \r\n"
			<<"float4 PSMain():SV_TARGET \r\n"
			<<"{ \r\n"
			<<"  return float4(1,1,1,1); \r\n"
			<<"} \r\n";
		String ts = shader.str();
		CompileMessageList messageList;
		gShader = gs->CreateGPUProgram("test_program", ts, ts, messageList); 
	}
}