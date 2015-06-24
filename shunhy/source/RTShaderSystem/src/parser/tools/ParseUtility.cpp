#include <stack>
#include "ParseUtility.h"
#include "CoreDef.h"
#include "Exceptions.h"
namespace shaderparser
{
	using namespace Shh;
	typedef std::vector<char*> StringCache;

	ShaderPropertyPtr		g_CurrentShader = nullptr;
	ProgramPropertyPtr		g_CurrentProgam = nullptr;
	TechniquePropertyPtr	g_CurrentTechnique = nullptr;
	PassPropertyPtr			g_CurrentPass = nullptr;
	StringCache				g_StringCache;
	ParseErrorPropertys		g_ErrorCache;
	std::stack<int>			g_StateStack;
	std::stack<BasePropertyPtr> g_CurrentPropertys;





	void __PushCurrentProperty(BasePropertyPtr ptr)
	{
		g_CurrentPropertys.push(ptr);
	}

	void __PopCurrentProperty()
	{
		g_CurrentPropertys.pop();
	}

	BasePropertyPtr __GetCurrentProperty()
	{
		return g_CurrentPropertys.top();
	}

	ShaderPropertyPtr __NewCurrentShader(int line, int position)
	{
		if (g_CurrentShader != nullptr)
		{
			SHH_EXCEPT(ShaderException, __shader_error1, __source_error);
		}
		g_CurrentShader = shh_new ShaderProperty;
		g_CurrentShader->SetBeginLine(line);
		g_CurrentShader->SetBeginPosition(position);
		return g_CurrentShader;
	}
	TechniquePropertyPtr __NewCurrentTechnique(int line, int position)
	{
		if (g_CurrentShader == nullptr)
		{
			SHH_EXCEPT(ShaderException, __technique_error1, __source_error);
		}
		g_CurrentTechnique = shh_new TechniqueProperty;
		g_CurrentTechnique->SetBeginLine(line);
		g_CurrentTechnique->SetBeginPosition(position);
		GetCurrentShader()->AddTechnique(GetCurrentTechnique());
		return g_CurrentTechnique;
	}
	PassPropertyPtr __NewCurrentPass(int line, int position)
	{
		if (g_CurrentTechnique == nullptr)
		{
			SHH_EXCEPT(ShaderException, __pass_error1, __source_error);
		}
		g_CurrentPass = new PassProperty;
		g_CurrentPass->SetBeginLine(line);
		g_CurrentPass->SetBeginPosition(position);
		GetCurrentTechnique()->AddPass(GetCurrentPass());
		return g_CurrentPass;
	}
	ProgramPropertyPtr __NewCurrentProgram(int line, int position)
	{
		if (g_CurrentShader == nullptr)
		{
			SHH_EXCEPT(ShaderException, __program_error2, __source_error);
		}
		if (GetCurrentShader()->GetProgram() != nullptr)
		{
			ParseError(__program_error1, line, position);
			SHH_EXCEPT(ShaderException, __program_error1, __source_error);
		}
		g_CurrentProgam = shh_new ProgramProperty;
		g_CurrentProgam->SetBeginLine(line);
		g_CurrentProgam->SetBeginPosition(position);
		GetCurrentShader()->SetProgram(GetCurrentProgram());
		return g_CurrentProgam;
	}



	int ParseInt(const char* p)
	{
		int v = atoi(p);
		return v;
	}

	float ParseFloat(const char* p)
	{
		float v = (float)atof(p);
		return v;
	}


	char* AllocString(const char *p)
	{
		int length = strlen(p);
		if (length > 0)
		{
			char* buf = new char[length + 1];
			g_StringCache.push_back(buf);
			memcpy( buf, p, length);
			buf[length] = 0;
			return buf;
		}
		return 0;
	}

	char* AllocString(const char* begin, const char* end)
	{
		int length = end - begin;
		if (length > 1)
		{
			--length;
			char* buf = new char[length + 1];
			g_StringCache.push_back(buf);
			memcpy( buf, begin, length);
			buf[length] = 0;
			return buf;
		}
		return 0;
	}

	int GetLineCount(const char* p)
	{
		if (p)
		{
			int l = 0;
			while(*p != 0)
			{
				if (ASCII_LF == *p)
				{
					++l;
				}
				++p;
			}
			return l;
		}
		return 0;
	}

	int PushLexerState(int state)
	{
		g_StateStack.push(state);
		return state;
	}

	int PopLexerState()
	{
		int top = g_StateStack.top();
		g_StateStack.pop();
		return top;
	}

	int ParseError (const char *s, int line, int position)
	{
		//n_printf("ShhShader Error: %s At line:%d\n",s,line);
		ParseErrorPropertyPtr ptr = new ParseErrorProperty;
		ptr->SetBeginLine(line);
		ptr->SetBeginPosition(position);
		ptr->SetMessage(s);
		ptr->SetName("error");
		g_ErrorCache.push_back(ptr);
		return 1;
	}

	void ResetParseCache()
	{
		FreeShader(g_CurrentShader);

		__for_each(ParseErrorPropertys, g_ErrorCache, it)
		{
			shh_delete *it;
		}

		__for_each(StringCache, g_StringCache, it)
		{
			shh_delete[] *it;
		}

		g_CurrentShader = nullptr;
		g_CurrentProgam = nullptr;
		g_CurrentTechnique = nullptr;
		g_CurrentPass = nullptr;
		g_StringCache.clear();
		g_ErrorCache.clear();
	}

	void FreeShader(ShaderPropertyPtr shader)
	{
		if (shader)
		{
			shh_delete shader;
		}
	}


	void FinishCurrentProperty()
	{
		GetCurrentProperty()->_Finish();
		__PopCurrentProperty();
	}

	BasePropertyPtr GetCurrentProperty()
	{
		return __GetCurrentProperty();
	}


	ShaderPropertyPtr  GetCurrentShader()
	{
		return g_CurrentShader;
	}

	TechniquePropertyPtr GetCurrentTechnique()
	{
		return g_CurrentTechnique;
	}
	ProgramPropertyPtr GetCurrentProgram()
	{
		return g_CurrentProgam;
	}
	PassPropertyPtr GetCurrentPass()
	{
		return g_CurrentPass;
	}
	const ParseErrorPropertys& GetErrors()
	{
		return g_ErrorCache;
	}

	BasePropertyPtr NewCurrentProperty(PropertyType pt, int lineno, int position)
	{
		BasePropertyPtr ptr = nullptr;
		switch(pt)
		{
		case PT_PassProperty:
			{
				ptr = __NewCurrentPass(lineno, position);
			}
			break;
		case PT_TechniqueProperty:
			{
				ptr = __NewCurrentTechnique(lineno, position);
			}
			break;
		case PT_ProgramProperty:
			{
				ptr = __NewCurrentProgram(lineno, position);
			}
			break;
		case PT_ShaderProperty:
			{
				ptr = __NewCurrentShader(lineno, position);
			}
			break;
		default:
			break;
		}
		__PushCurrentProperty(ptr);
		return nullptr;
	}

}