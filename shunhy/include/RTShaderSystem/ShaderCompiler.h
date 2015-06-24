#ifndef __SHADERCOMPILER_H__
#define __SHADERCOMPILER_H__
#include "RTShaderSystem/RTSSCommon.h"
#include "Core/Singleton.h"
#include "Resource/Resource.h"
#include "Graphics/GraphicsDef.h"
#include "DrawDrv/ResourceFactory.h"
namespace Shh
{
	class PropertyParsers;
	class _Shh_Export ShaderCompiler
	{
	public:
		ShaderCompiler();
		~ShaderCompiler();
		void Setup(Graphics* graphics);
		void Destroy();

		Shader* CompileShader(const U8String& file_name);

		static ShaderCompiler* CreateT();
		static void DeleteT(ShaderCompiler* sc);
	private:
		void setCommonShaderHead(const U8String& str);
		Graphics* mGraphics;
		PropertyParsers* mPassers;
		U8String mCommonShaderHead;
		U8String mCommonShaderEnd;
		U8String mShaderCache;
		int mCommonShaderHeadLineCount;
	};
}
#endif //__SHADERCOMPILER_H__