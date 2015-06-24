#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__
#include "MathCore/Matrix4.h"
#include "MathCore/BoundingBox.h"
#include "Graphics/GraphicsDef.h"
namespace Shh
{
	class SceneObject
	{
	public:

		virtual ~SceneObject();
		virtual void PushTo(Renderables& list) = 0;
		size_t GetTag() const;
		void SetTag(const size_t& tag);
		GraphicRenderer* GetRenderer() const;

	protected:
		SceneObject();
		void setRenderer(GraphicRenderer* renderer);
	private:
		GraphicRenderer* mRenderer;
		Matrix4 mTransfrom;
		BoundingBox mBounding;
		size_t mTag;
	};

	inline void SceneObject::SetTag(const size_t& tag)
	{
		mTag = tag;
	}

	inline size_t SceneObject::GetTag() const
	{
		return mTag;
	}

	inline GraphicRenderer* SceneObject::GetRenderer() const
	{
		return mRenderer;
	}

	inline void SceneObject::setRenderer(GraphicRenderer* renderer)
	{
		mRenderer = renderer;
	}

}


#endif //__SCENE_OBJECT_H__
