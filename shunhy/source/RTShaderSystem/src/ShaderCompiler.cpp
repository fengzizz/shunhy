#include <sstream>
#include "Core/Log.h"
#include "Core/CoreService.h"
#include "Core/StringUtility.h"
#include "Core/Convert.h"
#include "Core/FileSystem/FileSystem.h"
#include "Graphics/Graphics.h"
#include "Graphics/Shader.h"
#include "parser/ShaderParser.h"
#include "ShaderCompiler.h"

namespace Shh
{
#if __PRINT_ALL_DEBUG_LOG__
#	define __WRITE_SHADER__
#	define __SHADER_PARSE_DEBUG__
#endif

#ifdef __WRITE_SHADER__
	static String CompileShaderPath = "home:CompileShader";
#endif
	
#define __if_cmd(cmd, key, vcount) if (key == cmd && index + vcount < tokenCount)
#define __elif_cmd(cmd, key, vcount) else if (key == cmd && index + vcount < tokenCount)
#define __next(index) ++index

#define __property_error(_index) _property_error(tokens[_index].lineno, tokens[_index].position, tokens[_index].name)

#define __declare_sub_func(_Parent, _Index) \
	void _Parent##_Index(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)\
	{\
		_Parent(cmd, tokens, index, passData, _Index);\
	}\



	void _parse_error(int line, int position, const char* msg)
	{
		shh_log("parser error(%d,%d): %s", line, position, msg);
	}

	void _parse_debug_error(int line, int position, const char* msg)
	{
		shh_log("parser debug(%d,%d): %s", line, position, msg);
	}

	//void _parse_error(int line, const char* msg)
	//{
	//	shh_log("parser error(%d): %s", line, msg);
	//}

	void _property_error(int line, int position, const char* prop)
	{
		SSTREAM_COUT(msg)<<"syntax error"<<prop;
		_parse_error(line, position, prop);
	}



	class PassPragment
	{
	public:
		U8String surfaceName;
		U8String vsEntry;
		U8String psEntry;
	};

	struct PassData
	{
		RenderStateDesc::SamplerStateDic*			samplerStateDic;
		DeviceBlendState*							renderBlendState;
		DeviceRasterizerState*						renderRasterizerState;
		DeviceDepthAndStencilState*					renderDepthStencilState;
		PassPragment*								pragment;
		ShaderParameters*							parameters;
		PassData()
			:pragment(nullptr)
			,parameters(nullptr)
			,samplerStateDic(nullptr)
			,renderBlendState(nullptr)
			,renderRasterizerState(nullptr)
			,renderDepthStencilState(nullptr)
		{

		}
	};


	bool parseString(const shaderparser::PropertyTokens& tokens, int _index, shaderparser::PropertyToken::Code _code, U8String& _name) 
	{
		if (_index < (int)tokens.size())
		{
			if (_code != tokens[_index].code) 
			{
				__property_error(_index);
				return false;
			} 
			_name = tokens[_index].name;
			return true;
		}
		return false;
	}

	template<typename _Ty>
	bool parseEnumProperty(const shaderparser::PropertyTokens& tokens, int index, shaderparser::PropertyToken::Code code, _Ty& setting)
	{
		U8String name;
		if(!parseString(tokens, index, code, name)) 
		{
			__property_error(index);
			return false;
		}
		if(!_Ty::parse(name, setting))
		{		
			__property_error(index);
			return false;
		}
		return true;
	}

	bool parseFloatProperty(const shaderparser::PropertyTokens& tokens, int index, float& value)
	{
		U8String name;
		if(!parseString(tokens, index, shaderparser::PropertyToken::Value, name)) 
		{
			__property_error(index);
			return false;
		}
		if(utility::parseFloat(name, value))
		{
			return true;
		}
		else
		{
			__property_error(index);
			return false;
		}
	}
	bool parseFloatArrayProperty(const shaderparser::PropertyTokens& tokens, int index, Single* array, int len)
	{
		U8String name;
		if(!parseString(tokens, index, shaderparser::PropertyToken::String, name)) 
		{
			__property_error(index);
			return false;
		}
		static const U8String delims = ",";
		StringVector datas;
		utility::split(datas, name, delims);

		size_t minlen = ((size_t)len) < datas.size() ? len : datas.size();
		bool _return = true;
		for (size_t i = 0; i < minlen; ++i)
		{
			if(!utility::parseSingle(datas[i], array[i]))
			{
				__property_error(index);
				_return = false;
			}
		}
		return _return;
	}


	bool parseUInt8Property(const shaderparser::PropertyTokens& tokens, int index, uint8& value)
	{
		U8String name;
		if(!parseString(tokens, index, shaderparser::PropertyToken::Value, name)) 
		{
			__property_error(index);
			return false;
		}
		if(utility::parseUInt8(name, value))
		{
			return true;
		}
		else
		{
			__property_error(index);
			return false;
		}
	}
	bool parseBoolProperty(const shaderparser::PropertyTokens& tokens, int index, bool& value)
	{
		U8String name;
		if(!parseString(tokens, index, shaderparser::PropertyToken::Setting, name)) 
		{
			__property_error(index);
			return false;
		}
		if(utility::parseBool(name, value))
		{
			return true;
		}
		else
		{
			__property_error(index);
			return false;
		}
	}

	bool parseStringProperty(const shaderparser::PropertyTokens& tokens, int index, shaderparser::PropertyToken::Code code, U8String& str)
	{
		return parseString(tokens, index, code, str);
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void parseSurface(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		U8String name;
		if(!parseStringProperty(tokens, index, shaderparser::PropertyToken::Operator, name)) 
			return;

		if ("=" != name) 
			return;

		if(!parseStringProperty(tokens, index + 1, shaderparser::PropertyToken::Setting, passData.pragment->surfaceName))
			return;
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void parseFillMode(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderRasterizerState->fillMode);
	}

	void parseCullMode(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderRasterizerState->cullMode);
	}

	void parseDephBias(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseFloatProperty(tokens, index, passData.renderRasterizerState->depthBias);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void parseAlphaTest(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseBoolProperty(tokens, index, passData.renderBlendState->alphaTestEnable);
	}
	void parseAlphaFunction(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderBlendState->alphaFunc);
	}
	void parseAlphaRef(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseFloatProperty(tokens, index, passData.renderBlendState->alphaRef);
	}

	void checkBlendTargets(PassData& passData, int targetIndex)
	{
		if (targetIndex >= (int)passData.renderBlendState->targets.size())
		{
			passData.renderBlendState->targets.resize(targetIndex + 1);
		}
	}

	void parseBlendMode(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData, int targetIndex)
	{
		checkBlendTargets(passData, targetIndex);

		if (parseEnumProperty(tokens, index, shaderparser::PropertyToken::Key, passData.renderBlendState->targets[targetIndex].blendOP))
		{
			passData.renderBlendState->targets[targetIndex].alphaBlendEnable = true;
			parseEnumProperty(tokens, index + 1, shaderparser::PropertyToken::Setting, passData.renderBlendState->targets[targetIndex].srcBlend);
			parseEnumProperty(tokens, index + 2, shaderparser::PropertyToken::Setting, passData.renderBlendState->targets[targetIndex].destBlend);
		}
	}

	void parseBlendColorMask(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData, int targetIndex)
	{
		checkBlendTargets(passData, targetIndex);
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderBlendState->targets[targetIndex].colorWriteMask);
	}
	
	__declare_sub_func(parseBlendMode, 0);
	__declare_sub_func(parseBlendMode, 1);
	__declare_sub_func(parseBlendMode, 2);
	__declare_sub_func(parseBlendMode, 3);
	__declare_sub_func(parseBlendMode, 4);
	__declare_sub_func(parseBlendMode, 5);
	__declare_sub_func(parseBlendMode, 6);
	__declare_sub_func(parseBlendMode, 7);


	__declare_sub_func(parseBlendColorMask, 0);
	__declare_sub_func(parseBlendColorMask, 1);
	__declare_sub_func(parseBlendColorMask, 2);
	__declare_sub_func(parseBlendColorMask, 3);
	__declare_sub_func(parseBlendColorMask, 4);
	__declare_sub_func(parseBlendColorMask, 5);
	__declare_sub_func(parseBlendColorMask, 6);
	__declare_sub_func(parseBlendColorMask, 7);


	//-------------------------------------------------------------------------------------------------------------------------------------------------------
	void parseDepthTest(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseBoolProperty(tokens, index, passData.renderDepthStencilState->depthTestEnable);
	}

	void parseDepthWrite(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseBoolProperty(tokens, index, passData.renderDepthStencilState->depthWriteEnable);
	} 

	void parseDepthFunc(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->depthFunc);
	}

	void parseStencilEnable(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseBoolProperty(tokens, index, passData.renderDepthStencilState->stencilEnable);
	} 

	void parseStencilRef(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseUInt8Property(tokens, index, passData.renderDepthStencilState->stencilRef);
	}

	void parseStencilReadMask(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseUInt8Property(tokens, index, passData.renderDepthStencilState->stencilReadMask);
	}

	void parseStencilWriteMask(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseUInt8Property(tokens, index, passData.renderDepthStencilState->stencilWriteMask);
	}

	//
	void parseStencilFunc(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilFunc);
	}

	void parseStencilFail(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilFail);
	}

	void parseStencilZFail(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilZFail);
	}

	void parseStencilPass(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilPass);
	}
	//
	void parseStencilBackFunc(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilBackFunc);
		passData.renderDepthStencilState->stencilBackCustom = true;
	}

	void parseStencilBackFail(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilBackFail);
		passData.renderDepthStencilState->stencilBackCustom = true;
	}

	void parseStencilBackZFail(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilBackZFail);
		passData.renderDepthStencilState->stencilBackCustom = true;
	}

	void parseStencilBackPass(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		parseEnumProperty(tokens, index, shaderparser::PropertyToken::Setting, passData.renderDepthStencilState->stencilBackPass);
		passData.renderDepthStencilState->stencilBackCustom = true;
	}

	//-------------------------------------------------------------------------------------------------------------------------------------------------------

	void parseSamper(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		U8String name;
		if(!parseStringProperty(tokens, index, shaderparser::PropertyToken::Key, name)) 
			return;
		if (name.empty())
		{
			__property_error(index);
		}
		else
		{
			SamplerState state;
			parseEnumProperty(tokens, index + 1, shaderparser::PropertyToken::Setting, state.addressU);
			parseEnumProperty(tokens, index + 2, shaderparser::PropertyToken::Setting, state.Filter);
			state.addressV = state.addressW = state.addressU;
			passData.parameters->SetSampler(name, state);
		}
	}

	template<typename _Dt>
	bool parseContantData(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, U8String& name, _Dt& dt)
	{
		if(!parseStringProperty(tokens, index, shaderparser::PropertyToken::Key, name)) 
			return false;
		if (name.empty())
		{
			__property_error(index);
			return false;
		}
		else
		{
			parseFloatArrayProperty(tokens, index + 1, (_Dt::ValueType*)&dt, _Dt::ElementCount);
			return true;
		}
	}

	void parseVector(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		Vector4 v4;
		U8String name;
		if(parseContantData(cmd, tokens, index, name, v4))
		{
			passData.parameters->SetVector(name, v4);
		}
	}

	void parseMatrix(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData)
	{
		Matrix4 m4;
		U8String name;
		if(parseContantData(cmd, tokens, index, name, m4))
		{
			passData.parameters->SetMatrix(name, m4);
		}
	}


	typedef void (*pParseFunction)(const shaderparser::PropertyToken& cmd, const shaderparser::PropertyTokens& tokens, int index, PassData& passData);
	struct PropertyParser
	{
		PropertyParser()
			:parameterCount(0)
			,function(nullptr)
		{

		}
		PropertyParser(int pCount, pParseFunction pf)
			:parameterCount(pCount)
			,function(pf)
		{
		}
		inline bool valid() const
		{
			return function != nullptr;
		}
		pParseFunction function;
		int parameterCount;
	};
	typedef std::map<U8String, PropertyParser> PropertyParserMap;
	class PropertyParsers
	{
	public:
		PropertyParsers();
		const PropertyParser& find(const U8String& name) const;
	private:
		PropertyParserMap parsers;
		static PropertyParser defaultParser;
	};
	PropertyParser PropertyParsers::defaultParser(0, nullptr);

	PropertyParsers::PropertyParsers()
	{
		parsers["surface"] = PropertyParser(2, parseSurface);

		// DeviceRasterizerState
		parsers["cullmode"] = PropertyParser(1, parseCullMode);
		parsers["filemode"] = PropertyParser(1, parseFillMode);
		parsers["depthbias"] = PropertyParser(1, parseDephBias);

		// DeviceBlendState
		parsers["alphatest"] = PropertyParser(1, parseAlphaTest);
		parsers["alphafunc"] = PropertyParser(1, parseAlphaFunction);
		parsers["alpharef"] = PropertyParser(1, parseAlphaRef);

		parsers["blendmode"] = PropertyParser(3, parseBlendMode0);
		parsers["blendmode0"] = PropertyParser(3, parseBlendMode0);
		parsers["blendmode1"] = PropertyParser(3, parseBlendMode1);
		parsers["blendmode2"] = PropertyParser(3, parseBlendMode2);
		parsers["blendmode3"] = PropertyParser(3, parseBlendMode3);
		parsers["blendmode4"] = PropertyParser(3, parseBlendMode4);
		parsers["blendmode5"] = PropertyParser(3, parseBlendMode5);
		parsers["blendmode6"] = PropertyParser(3, parseBlendMode6);
		parsers["blendmode7"] = PropertyParser(3, parseBlendMode7);

		parsers["colormask"] = PropertyParser(1, parseBlendColorMask0);
		parsers["colormask0"] = PropertyParser(1, parseBlendColorMask0);
		parsers["colormask1"] = PropertyParser(1, parseBlendColorMask1);
		parsers["colormask2"] = PropertyParser(1, parseBlendColorMask2);
		parsers["colormask3"] = PropertyParser(1, parseBlendColorMask3);
		parsers["colormask4"] = PropertyParser(1, parseBlendColorMask4);
		parsers["colormask5"] = PropertyParser(1, parseBlendColorMask5);
		parsers["colormask6"] = PropertyParser(1, parseBlendColorMask6);
		parsers["colormask7"] = PropertyParser(1, parseBlendColorMask7);

		// DeviceDepthAndStencilState
		parsers["depthfunc"] = PropertyParser(1, parseDepthFunc);

		parsers["stencilfunc"] = PropertyParser(1, parseStencilFunc);
		parsers["stencilfail"] = PropertyParser(1, parseStencilFail);
		parsers["stencilzfail"] = PropertyParser(1, parseStencilZFail);
		parsers["stencilpass"] = PropertyParser(1, parseStencilPass);
		parsers["stencilbackfunc"] = PropertyParser(1, parseStencilBackFunc);
		parsers["stencilbackfail"] = PropertyParser(1, parseStencilBackFail);
		parsers["stencilbackzfail"] = PropertyParser(1, parseStencilBackZFail);
		parsers["stencilbackpass"] = PropertyParser(1, parseStencilBackPass);

		parsers["stencilref"] = PropertyParser(1, parseStencilRef);
		parsers["stencilreadmask"] = PropertyParser(1, parseStencilReadMask);
		parsers["stencilwitemask"] = PropertyParser(1, parseStencilWriteMask);

		parsers["depthtest"] = PropertyParser(1, parseDepthTest);
		parsers["depthwrite"] = PropertyParser(1, parseDepthWrite);
		parsers["stencil"] = PropertyParser(1, parseStencilEnable);

		//
		parsers["sampler"] = PropertyParser(3, parseSamper);
		parsers["samplerstate"] = PropertyParser(3, parseSamper);

		parsers["vector"] = PropertyParser(2, parseVector);
		parsers["matrix"] = PropertyParser(2, parseMatrix);
	}
	const PropertyParser& PropertyParsers::find(const U8String& name) const
	{
		PropertyParserMap::const_iterator it = parsers.find(name);
		if (it != parsers.end())
		{
			return it->second;
		}
		return defaultParser;
	}

	void parsePassPropertys(PropertyParsers* parsers, ShaderPass* pass, shaderparser::PassPropertyPtr props, PassPragment& pragment)
	{
		RenderStateDesc::SamplerStateDic			samplerStateDic;
		DeviceBlendState							renderBlendState;
		DeviceRasterizerState						renderRasterizerState;
		DeviceDepthAndStencilState					renderDepthStencilState;

		PassData passData;
		passData.samplerStateDic = &samplerStateDic;
		passData.renderBlendState = &renderBlendState;
		passData.renderRasterizerState = &renderRasterizerState;
		passData.renderDepthStencilState = &renderDepthStencilState;
		passData.pragment = &pragment;
		passData.parameters = &pass->_GetParameters();

		const shaderparser::PropertyTokens& tokens = props->GetTokens();
		size_t tokenCount = tokens.size();
		for (size_t index = 0; index < tokenCount; __next(index))
		{
			const shaderparser::PropertyToken& cmd = tokens[index];
			if (shaderparser::PropertyToken::CMD == cmd.code)
			{
				U8String cmdname = cmd.name;
				utility::toLowerCase(cmdname);

				const PropertyParser& parser = parsers->find(cmdname);

				if (parser.valid())
				{
					if (index + parser.parameterCount < tokenCount)
					{
						parser.function(cmd, tokens, index + 1, passData);					
					}
					else
					{
						__property_error(index);
					}
				}
			}
		}
		RenderStateDesc& desc = pass->_GetDesc();
		desc.SetSamplerState(samplerStateDic);
		desc.SetBlendState(renderBlendState);
		desc.SetRasterizerState(renderRasterizerState);
		desc.SetDepthAndStencilState(renderDepthStencilState);
	}


	ShaderCompiler::ShaderCompiler()
		:mGraphics(nullptr)
		,mPassers(nullptr)
		,mCommonShaderHeadLineCount(0)
	{

	}

	ShaderCompiler::~ShaderCompiler()
	{
	}

	void ShaderCompiler::setCommonShaderHead(const U8String& str)
	{
		mCommonShaderHead = str;
		mCommonShaderHeadLineCount = utility::lineCount(str);
	}

	void ShaderCompiler::Setup(Graphics* graphics)
	{
		mPassers = shh_new PropertyParsers();
		mGraphics = graphics;
		DrawDrvCode ddt = mGraphics->GetDriverType();
		CoreService& cs = CoreService::GetSingleton();
		U8String head;
		U8String end;
		if (DrawDrv_D3D11 == ddt)
		{		
			head = "system:common_head11.shader";
			end = "system:common_end11.shader";
		}			
		else
		{
			return;
		}
		DataStreamPtr head_file = cs.GetFileSystem()->open(head, true);

		setCommonShaderHead(head_file->getAsString());

		head_file->close();

		DataStreamPtr end_file = cs.GetFileSystem()->open(end, true);
		mCommonShaderEnd = end_file->getAsString();
		end_file->close();
#ifdef __WRITE_SHADER__
		cs.GetFileSystem()->createPath(CompileShaderPath);
#endif
	}

	void ShaderCompiler::Destroy()
	{
		shh_delete mPassers;
		mPassers = nullptr;
	}


	Shader* ShaderCompiler::CompileShader(const U8String& file_name)
	{
		CoreService& cs = CoreService::GetSingleton();
		DataStreamPtr file_stream = cs.GetFileSystem()->open(file_name, true);
		U8String temp = file_stream->getAsString();
		file_stream->close();
		shh_log("compile shader: %s\n", file_name.c_str()); 

		shaderparser::ShaderPropertyPtr shader_info = shaderparser::ParseShader(temp);

		const shaderparser::ParseErrorPropertys& errors = shaderparser::GetParseErrors();

		__for_each(shaderparser::ParseErrorPropertys, errors, it)
		{
			_parse_error((*it)->GetBeginLine(), (*it)->GetBeginPosition(), (*it)->GetMessage().c_str());
		}
		Shader* shader = nullptr;
		if (shader_info)
		{
			shader = shh_new Shader();
			shader->SetName(NameString::from(file_name));
			__for_each(shaderparser::TechniquePropertys, shader_info->GetTechniques(), it)
			{
				Technique* tech = shh_new Technique();
				tech->SetName((*it)->GetName());
				shader->_AddTech(tech);
				__for_each(shaderparser::PassPropertys, (*it)->GetPasses(), itp)
				{
					ShaderPass* pass = shh_new ShaderPass();
					pass->SetName((*itp)->GetName());

					PassPragment pragment;
					parsePassPropertys(mPassers, pass, *itp, pragment);

					U8String macro;
					shaderparser::ProgramPropertyPtr program = shader_info->GetProgram();
					if (!pragment.surfaceName.empty() && program)
					{
						macro = "#define SURFACE_BRUSH " + pragment.surfaceName + "\n";//macro = "#define SURFACE_BRUSH(x) { return (SurfaceOut)0; }\n";

						mShaderCache = mCommonShaderHead + program->GetCode() + macro + mCommonShaderEnd;
						CompileMessageList cmesgs;
						RenderHandle handle = mGraphics->CreateGPUProgram(file_name, mShaderCache, mShaderCache, cmesgs);

						__for_each(CompileMessageList, cmesgs, it)
						{
							int lineon = (*it).LineOn - mCommonShaderHeadLineCount + program->GetBeginLine();
							if (program->GetBeginLine() <= lineon && lineon <= program->GetTailLine())
							{
								_parse_error(lineon, (*it).Position, (*it).Message.c_str());
							}
							else
							{
								if (handle.IsValid())
								{
#ifdef __SHADER_PARSE_DEBUG__
									_parse_debug_error((*it).LineOn, (*it).Position, (*it).Message.c_str());
#endif
								}
								else
								{
									_parse_error(lineon, (*it).Position, (*it).Message.c_str());
								}

							}
						}

						pass->_SetGPUProgramHandle(handle);

#ifdef __WRITE_SHADER__
						SSTREAM_COUT(output)<<CompileShaderPath<<"/"<<file_name.substr(file_name.rfind(':') + 1)<<"_"<<tech->GetName()<<"_"<<pass->GetName()<<".shader"; 
						DataStreamPtr file_stream2 = cs.GetFileSystem()->createFile(output.str());
						file_stream2->write(mShaderCache.c_str(), mShaderCache.size());
						file_stream2->close();
#endif
					}

					tech->_AddPass(pass);
				}
			}

		}
		shaderparser::FreeShader();
		return shader;
	}

	ShaderCompiler* ShaderCompiler::CreateT()
	{
		return shh_new ShaderCompiler;
	}
	
	void ShaderCompiler::DeleteT(ShaderCompiler* sc)
	{
		shh_delete sc;
	}
}