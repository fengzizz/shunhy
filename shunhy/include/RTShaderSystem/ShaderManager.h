#pragma once
#include "Singleton.h"
#include "RTShaderSystem/RTSSCommon.h"
namespace Shh
{
	class _Shh_Export ShaderManager : Singleton<ShaderManager>
	{
	public:
		~ShaderManager();
	private:
		ShaderManager();

		//ShaderProgram*
	};
}