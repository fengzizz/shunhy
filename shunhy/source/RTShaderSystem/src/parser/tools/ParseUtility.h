#ifndef __PARSER_UTILITY_H__
#define __PARSER_UTILITY_H__
#include "Debug.h"
#include "../ShaderParser.h"

//#ifdef __PRINT_ALL_DEBUG_LOG__
//#	define __PARSING_LOG__ 
//#endif

#ifdef __PARSING_LOG__
#	define YYERROR_VERBOSE //more info for parse.
#	define YYDEBUG 1 // 将这个变量设置为1 则表示启动Yacc的调试功能
#endif // _DEBUG


#define __source_error "parsing shader"
#define __shader_error1 "current shader is not null"
#define __technique_error1 "shader instance is null, when try to parse a technique"

#define __pass_error1 "technique instance is null, when try to parse a pass"

#define __program_error1 "only one program area in a shader"
#define __program_error2 "shader instance is null, when try to parse program area"


typedef struct __YY_STYPE__
{
	__YY_STYPE__()
	{
		str = 0;
		lineno = -1;
		position = -1;
	}
	union {
		char* str;
		int num;
		float single;
		bool boolean;
	};
	int lineno;
	int position;
} _YY_STYPE;
#define YYSTYPE _YY_STYPE

typedef struct __YYLTYPE
{
	int first_line;
	int first_column;
	int last_line;
	int last_column;
	__YYLTYPE()
	{
		first_line = first_column = last_column = last_line = 1;
	}
} YYLTYPE;

extern YYLTYPE yylloc;

inline void yy_user_action(YYLTYPE& loc, int lineno, int charcount, const char* text)
{
	int slen = charcount;
	const char* ptr = text;
	if (0 != text)
	{
		if (*ptr < 32) // centrol chars in front.
		{	
			slen = 0;
			while(32 > *ptr && 0 != *ptr)
			{
				switch(*ptr)
				{
				case ASCII_TAB:
					{
						slen += 4;
						break;
					}
				default:
					break;
				}
				++ptr;
			}
			
		}
	}

	loc.last_line = lineno; 
	if (loc.last_line != loc.first_line)
	{
		int fline = lineno;
		while (0 != *ptr) // centrol chars in no front.
		{
			switch(*ptr)
			{
			case ASCII_LF:
				{
					--fline;
					break;
				}
			default:
				break;
			}
			++ptr;
		}
		if (loc.first_line != fline)
		{
			loc.first_line = fline;	
			loc.last_column = 1;
		}

	}
	loc.first_column = loc.last_column;      

	//shh_log("(%d,%d): %s", loc.first_line, loc.first_column, text);
	loc.last_column += slen; 
}

#define YY_USER_ACTION  yy_user_action(yylloc, yylineno, yyleng, yytext);




inline void setyylineno(YYSTYPE& yyst, int lineno, int position)
{
	yyst.lineno = lineno;
	yyst.position = position;
}
#define __GET_YYLINENO() yylineno
#define __SET_YYLVAL_LINENO() setyylineno(yylval, yylloc.first_line, yylloc.first_column)



#define __SET_YYLVAL(_type, _value) \
	yylval._type = _value;\
	__SET_YYLVAL_LINENO()


#ifdef __PARSING_LOG__
#	define _DO_AND_LOG_(a) a; shh_log(#a)
#	define _PARSING_LOG_(a) shh_log(a)
#else
#	define _DO_AND_LOG_(a) a
#	define _PARSING_LOG_(a)
#endif // _DEBUG


namespace shaderparser
{

	enum PropertyType
	{
		PT_ShaderProperty,
		PT_TechniqueProperty,
		PT_PassProperty,
		PT_ProgramProperty,
	};

	int PushLexerState(int state);

	int PopLexerState();

	void InitShaderLexer(const char *c, size_t length);

	void ParseShader();

	void EndShaderLexer();

	int ParseInt(const char* p);

	float ParseFloat(const char* p);

	char* AllocString(const char* p);

	char* AllocString(const char* begin, const char* end);

	int GetLineCount(const char* p);

	int ParseError (const char *s, int line, int position);

	void ResetParseCache();

	void FreeShader(ShaderPropertyPtr shader);

	void FinishCurrentProperty();
	BasePropertyPtr GetCurrentProperty();
	ShaderPropertyPtr  GetCurrentShader();
	TechniquePropertyPtr GetCurrentTechnique();
	ProgramPropertyPtr GetCurrentProgram();
	PassPropertyPtr GetCurrentPass();
	const ParseErrorPropertys& GetErrors();

	BasePropertyPtr NewCurrentProperty(PropertyType pt, int lineno, int position);

}


#endif //__PARSER_UTILITY_H__