#ifndef __GRAPHICESCONFIG_H__
#define __GRAPHICESCONFIG_H__

#include "Core/CoreDef.h"
#include "Core/SharedObjectPtr.h"
#include "Core/Debug.h"


namespace Shh
{
	class Graphics;
	class GraphicSystem;
	class ShaderPass;
	class Technique;
	class Shader;
	class Material;
	class RenderHandle;
	class SceneSystem;
	class SceneObject;
	class Scene;
	class GraphicRenderer;
	class Renderable;

	typedef std::vector<SceneObject*> RenderObjects;
	typedef std::vector<Renderable*> Renderables;
}


#endif //__GRAPHICESCONFIG_H__
