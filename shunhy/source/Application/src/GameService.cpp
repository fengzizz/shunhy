
#include "Graphics/Graphics.h"
#include "Graphics/Scene.h"
#include "Graphics/SceneSystem.h"
#include "Resource/Resource.h"

#include "GameService.h"
namespace Shh
{
	SingletonInstancePtr(GameService);
	GameService::GameService()
	{
		
	}
	GameService::~GameService()
	{

	}

	void GameService::Setup(size_t width, size_t height, size_t handle, bool fullScrean)
	{
		if (mGraphics.empty())
		{
			mGraphics.create();
		}
		if (mResourceManager.empty())
		{
			mResourceManager.create();
		}
		if (mSceneSystem.empty())
		{
			mSceneSystem.create();
		}
		mGraphics->Setup(width, height, handle, fullScrean, DrawDrv_D3D11);
		mResourceManager->Setup(mGraphics.get());

		//test ..... 
		//auto shader = mResourceManager.GetShader("asset:system/default.shader");
	}

	void GameService::Start()
	{
	}

	void GameService::Destroy()
	{
		mGraphics->Destroy();
	}

	void GameService::Tick()
	{
		mSceneSystem->Tick();

		const RenderObjects& culls = mSceneSystem->GetCullObjects();

		mGraphics->BeginScene();
		mGraphics->Render(culls);
		mGraphics->EndScene();
	}
}