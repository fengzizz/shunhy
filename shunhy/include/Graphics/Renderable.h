#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include "Graphics/GraphicsDef.h"
namespace Shh
{
	class Renderable
	{
	public:
		virtual ~Renderable();
		SceneObject* GetSceneObject() const;
	protected:
		Renderable();
		void setSceneObject(SceneObject* sceneObject);
	private:
		SceneObject* mOwner;
	};

	inline SceneObject* Renderable::GetSceneObject() const
	{
		return mOwner;
	}

	inline void Renderable::setSceneObject(SceneObject* sceneObject)
	{
		mOwner = sceneObject;
	}

}


#endif //__RENDERABLE_H__
