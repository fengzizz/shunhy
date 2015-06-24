#ifndef __SHADER_PARSER_H__
#define __SHADER_PARSER_H__
#include <string>
#include <vector>
#include <map>
#include "Core/UniquePtr.h"
#include "DrawDrv/RenderState.h"
namespace shaderparser
{
	class TokenManager;
	class BaseProperty;
	class TechniqueProperty;
	class ProgramProperty;
	class PassProperty;
	class ShaderProperty;
	class ParseErrorProperty;

	typedef TokenManager* TokenManagerPtr;

	typedef BaseProperty* BasePropertyPtr;
	typedef ProgramProperty* ProgramPropertyPtr;
	typedef TechniqueProperty* TechniquePropertyPtr;
	typedef PassProperty* PassPropertyPtr;
	typedef ShaderProperty* ShaderPropertyPtr;
	typedef ParseErrorProperty* ParseErrorPropertyPtr;

	typedef std::vector<TechniquePropertyPtr> TechniquePropertys;	
	typedef std::vector<PassPropertyPtr> PassPropertys;
	typedef std::vector<ParseErrorPropertyPtr> ParseErrorPropertys;


	const ShaderPropertyPtr ParseShader(const std::string& code);
	void FreeShader();

	const ParseErrorPropertys& GetParseErrors();


	struct PropertyToken
	{
		inline PropertyToken()
			:code(Unknown)
			,name(0)
			,lineno(-1)
			,position(-1)
		{

		}
		enum Code
		{
			Operator,
			Unknown,
			CMD,
			Discribe,
			String,
			Key,
			Value,
			Setting,
		};
		Code code;
		const char* name;
		int lineno;
		int position;
	};
	typedef std::vector<PropertyToken> PropertyTokens;

	class TokenManager
	{
		//__Dynamic_Alloc(TokenManager);
	public:
		void Clear();
		void PushToken(PropertyToken::Code code, const char* name, int line, int position);
		const PropertyTokens& GetTokens() const;

	private:
		PropertyTokens pools;
	};

	class BaseProperty
	{
	public:
		inline BaseProperty()
			:begin_line(-1)
			,begin_position(-1)
		{

		}
		virtual ~BaseProperty();

		void PushToken(PropertyToken::Code code, const char* name, int line, int position);

		inline void SetName(const char* n)
		{
			name = n;
		}

		inline void SetBeginLine(int line)
		{
			begin_line = line;
		}

		inline void SetBeginPosition(int position)
		{
			begin_position = position;
		}

		inline const std::string& GetName() const
		{
			return name;
		}

		inline int GetBeginLine() const
		{
			return begin_line;
		}

		inline int GetBeginPosition() const
		{
			return begin_position;
		}

		inline const PropertyTokens& GetTokens() const
		{
			return tokens.GetTokens();
		}

		//internal call.
		void _Finish();
	protected:
		virtual void finish();
	private:
		TokenManager tokens;
		std::string name;
		int begin_line;
		int begin_position;
	};

	class PassProperty : public BaseProperty
	{
		__Super(BaseProperty);
	public:
		virtual ~PassProperty();
	private:
	};


	class TechniqueProperty : public BaseProperty
	{
		__Super(BaseProperty);
	public:
		virtual ~TechniqueProperty();
		inline void AddPass(PassPropertyPtr pass)
		{
			passes.push_back(pass);
		}

		inline const PassPropertys& GetPasses() const
		{
			return passes;
		}
	private:
		PassPropertys passes;
	};


	class ProgramProperty : public BaseProperty
	{
		__Super(BaseProperty);
	public:
		inline ProgramProperty()
			:head_len(0)
			,tail_len(0)
		{

		}
		virtual ~ProgramProperty();
		inline void SetHeadLen(int len)
		{
			head_len = len;
		}
		inline void SetTailLen(int len)
		{
			tail_len = len;
		}

		inline void SetTailLine(int line)
		{
			tail_line = line;
		}

		inline void SetTailPosition(int position)
		{
			tail_position = position;
		}
		
		inline int GetHeadLen() const
		{
			return head_len;
		}

		inline int GetTailLen() const
		{
			return tail_len;
		}

		inline int GetTailLine() const
		{
			return tail_line;
		}

		inline int GetTailPosition() const
		{
			return tail_position;
		}

		inline const std::string& GetCode() const
		{
			return code;
		}
	protected:
		virtual void finish();
	private:
		void _build(const std::string& shader);
		int head_len;
		int tail_len;
		int tail_line;
		int tail_position;
		std::string code;
		static const std::string HEAD_KEY;
		static const std::string TAIL_KEY;
	};


	class ShaderProperty : public BaseProperty
	{
		__Super(BaseProperty);
	public:
		virtual ~ShaderProperty();
		inline ShaderProperty()
			:program(nullptr)
		{

		}
		inline void AddTechnique(TechniquePropertyPtr tech)
		{
			techniques.push_back(tech);
		}
		inline void SetProgram(ProgramPropertyPtr prog)
		{
			program = prog;
		}

		inline const TechniquePropertys& GetTechniques() const
		{
			return techniques;
		}
		inline ProgramPropertyPtr GetProgram() const
		{
			return program;
		}
	private:
		TechniquePropertys techniques;
		ProgramPropertyPtr program;
	};

	class ParseErrorProperty : public BaseProperty
	{
		__Super(BaseProperty);
	public:
		virtual ~ParseErrorProperty();
		inline void SetMessage(const std::string& msg)
		{
			message = msg;
		}
		inline const std::string& GetMessage() const
		{
			return message;
		}
	private:
		std::string message;
	};
}


#endif //__SHADER_PARSER_H__