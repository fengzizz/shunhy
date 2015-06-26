#ifndef __RESOURCE_MANAGER_H__
#define __RESOURCE_MANAGER_H__

#include <map>
#include "Core/HString.h"
#include "Core/UniquePtr.h"
#include "Graphics/GraphicsDef.h"
#include "RTShaderSystem/RTSSCommon.h"
#include "Resource/Resource.h"

namespace Shh
{		
	typedef sptr<Shader> ShaderPtr;
	class ResourceManager
	{
		__Dynamic_Alloc(ResourceManager);
	public:

		ResourceManager();
		~ResourceManager();

		void Setup(Graphics* gr);

		ShaderPtr GetShader(const ResourceURI& name);

		static const U8String DefaultShaderName;
	private:
		typedef ResourceURI KeyType;
		typedef std::map<KeyType, ShaderPtr> ShaderResources;

		ShaderPtr loadShader(const ResourceURI& name);

		ShaderResources mShaders;

		uptr<ShaderCompiler> mShaderCompiler;
		Graphics* mGraphics;
	};
}


#endif //__RESOURCE_MANAGER_H__