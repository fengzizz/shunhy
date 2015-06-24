#ifndef __GAMESERVICE_H__
#define __GAMESERVICE_H__
#include "Core/Singleton.h"
#include "Graphics/GraphicsDef.h"
#include "Resource/ResourceManager.h"

#include "Application/AppDef.h"
#include "PrivateDef.h"
namespace Shh
{
	class GameService : public Singleton<GameService>
	{
		__Dynamic_Alloc(GameService);
	public:
		void Start();
		void Setup(size_t width, size_t height, size_t handle, bool fullScrean);
		void Tick();
		void Destroy();
		bool CheckExit();
	private:
		GameService();
		~GameService();
		uptr<Graphics> mGraphics;
		uptr<ResourceManager> mResourceManager;
		uptr<SceneSystem> mSceneSystem;
	};

}

#endif //__GAMESERVICE_H__