#include "CoreDef.h"
#include "tools/ParseUtility.h"
#include "ShaderParser.h"



namespace shaderparser
{
	static const std::string* g_CurrentCode = nullptr;

	const ShaderPropertyPtr ParseShader(const std::string& code)
	{
		ResetParseCache();
		try{
			g_CurrentCode = &code;
			InitShaderLexer(code.c_str(), code.size());
			ParseShader();

			EndShaderLexer();
			g_CurrentCode = nullptr;
		}
		catch(Shh::Exception e)
		{
			ParseError(e.GetDescription().c_str(), -1, -1);
			g_CurrentCode = nullptr;
			return nullptr;
		}

		return GetCurrentShader();
	}

	void FreeShader()
	{
		ResetParseCache();
	}

	const ParseErrorPropertys& GetParseErrors()
	{
		return GetErrors();
	}



	void TokenManager::Clear()
	{
		pools.clear();
	}

	void TokenManager::PushToken(PropertyToken::Code code, const char* name, int line, int position)
	{
		PropertyToken token;
		token.code = code;
		token.name = name;
		token.lineno = line;
		token.position = position;
		pools.push_back(token);
	}

	const PropertyTokens& TokenManager::GetTokens() const
	{
		return pools;
	}



	BaseProperty::~BaseProperty()
	{

	}
	 
	void BaseProperty::_Finish()
	{
		finish();
	}

	void BaseProperty::finish()
	{

	}

	void BaseProperty::PushToken(PropertyToken::Code code, const char* name, int line, int position)
	{
		//if (tokens.empty())
		//{
		//	tokens.create();
		//}
		tokens.PushToken(code, name, line, position);
	}

	PassProperty::~PassProperty()
	{

	}

	TechniqueProperty::~TechniqueProperty()
	{
		__for_each(shaderparser::PassPropertys, passes, pit)
		{
			shh_delete *pit;
		}
		passes.clear();
	}

	const std::string ProgramProperty::HEAD_KEY = "SHADER_CODE_BEGIN";
	const std::string ProgramProperty::TAIL_KEY = "SHADER_CODE_END";

	ProgramProperty::~ProgramProperty()
	{

	}

	void ProgramProperty::finish()
	{
		_build(*g_CurrentCode);
		super::finish();
	}

	void ProgramProperty::_build(const std::string& shader)
	{
		int h_pos = shader.find(HEAD_KEY) + head_len;
		int t_pos = shader.find(TAIL_KEY) + TAIL_KEY.size() - tail_len;
		code = shader.substr(h_pos, t_pos - h_pos);
	}

	ShaderProperty::~ShaderProperty()
	{
		__for_each(shaderparser::TechniquePropertys, techniques, tit)
		{
			shh_delete *tit;
		}
		shh_delete program;
		program = nullptr;
		techniques.clear();

	}

	ParseErrorProperty::~ParseErrorProperty()
	{

	}
}