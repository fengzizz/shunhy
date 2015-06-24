#include "Core/Log.h"
#include "RTShaderSystem/ShaderCompiler.h"
#include "Graphics/Shader.h"
#include "Resource.h"
#include "ResourceManager.h"


namespace Shh
{

	const U8String ResourceManager::DefaultShaderName = "system:default.shader";
	ResourceManager::ResourceManager()
		:mGraphics(nullptr)
	{

	}

	ResourceManager::~ResourceManager()
	{
		mGraphics = nullptr;
	}

	void ResourceManager::Setup(Graphics* gr)
	{
		mShaderCompiler.create();
		mShaderCompiler->Setup(gr);
		mGraphics = gr;

		////test shader parser
		//shh_log("test shader parser.");
		//GetShader(ResourceURI::from("asset:test.shader"));

		//// --------------------------
		GetShader(ResourceURI::from(DefaultShaderName));

	}

	ShaderPtr ResourceManager::GetShader(const ResourceURI& name)
	{
		ShaderPtr shader;
		ShaderResources::iterator it = mShaders.find(name);
		if (mShaders.end() == it)
		{
			shader = loadShader(name);
			if (shader)
			{
				mShaders.insert(ShaderResources::value_type(name, shader));
			}
		}
		else
		{
			shader = it->second;
		}
		return shader;
	}

	ShaderPtr ResourceManager::loadShader(const ResourceURI& name)
	{
		return ShaderPtr(mShaderCompiler->CompileShader(name.string()));
	}
}