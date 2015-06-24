#include "Shader.h"

namespace Shh
{
	ShaderPass::ShaderPass()
	{

	}

	void Technique::_AddPass(ShaderPass* pass)
	{
		shh_assert(nullptr != pass);
		mPasses.push_back(pass);
	}



	void Shader::_AddTech(Technique* tech)
	{
		shh_assert(nullptr != tech);
		mTechniques.push_back(tech);
	}
}