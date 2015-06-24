#ifndef __SCENE_H__
#define __SCENE_H__
#include <set>
#include "Core/SObject.h"
#include "Core/Nameable.h"
#include "Graphics/GraphicsDef.h"

namespace Shh
{		
	class _Shh_Export Scene : public SObject, public Nameable
	{
	public:
		typedef SceneObject* SceneObjectPtr;
		typedef std::vector<SceneObjectPtr> SceneObjects;
		Scene();
		virtual ~Scene();
		virtual void Add(SceneObjectPtr object) = 0;
		virtual void Remove(SceneObjectPtr object) = 0;
		virtual void Cull(SceneObjects& list) = 0;
	};

	class _Shh_Export SimpleScene : public Scene
	{
	public:
		virtual void Add(SceneObjectPtr object);
		virtual void Remove(SceneObjectPtr object) ;
		virtual void Cull(SceneObjects& list);
	private:
		std::set<Scene::SceneObjectPtr> mSceneObjects;
	};

}


#endif //__SCENE_H__