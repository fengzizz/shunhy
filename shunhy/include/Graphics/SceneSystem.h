#ifndef __SCENE_SYSTEM_H__
#define __SCENE_SYSTEM_H__
#include <vector>
#include "Core/Singleton.h"
#include "Core/SharedObjectPtr.h"
#include "Graphics/GraphicsDef.h"
namespace Shh
{
	class _Shh_Export SceneSystem : public Singleton<SceneSystem>
	{
		__Dynamic_Alloc(SceneSystem);
	public:	
		typedef sptr<Scene> ScenePtr;
		void Tick();
		void Add(const sptr<Scene>& scene);//(const sptr<Scene>& scene);
		void Add(Scene* scene);//(const sptr<Scene>& scene);
		const RenderObjects& GetCullObjects() const;
	private:
		typedef std::vector<ScenePtr> scenes;
		scenes mScenes;
		RenderObjects mCullObjects;
	};

	inline const RenderObjects& SceneSystem::GetCullObjects() const
	{
		return mCullObjects;
	}

}


#endif //__SCENE_SYSTEM_H__
