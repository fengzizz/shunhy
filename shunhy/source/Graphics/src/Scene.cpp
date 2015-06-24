#include "Scene.h"

namespace Shh
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}


	void SimpleScene::Add(SceneObjectPtr object)
	{
		mSceneObjects.insert(object);
	}

	void SimpleScene::Remove(SceneObjectPtr object)
	{
		mSceneObjects.erase(object);
	}

	void SimpleScene::Cull(SceneObjects& list)
	{
		list.assign(mSceneObjects.begin(), mSceneObjects.end());
	}
}
