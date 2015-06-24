#include "Scene.h"
#include "SceneSystem.h"


namespace Shh
{

	SingletonInstancePtr(SceneSystem);


	void SceneSystem::Tick() 
	{
		mCullObjects.clear();
		__for_each(scenes, mScenes, it)
		{
			(*it)->Cull(mCullObjects);
		}
	}

	void SceneSystem::Add(const sptr<Scene>& scene)
	{
		mScenes.push_back(scene);
	}

	void SceneSystem::Add(Scene* scene)
	{
		Add(sptr<Scene>(scene));
	}
}