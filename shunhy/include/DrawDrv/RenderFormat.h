#pragma once

#include "Core/TEnum.h"
#include "Core/CoreDef.h"
#include "Core/IRelease.h"
#include "Core/U8String.h"
#include "DrawDrv/PixelFormat.h"

namespace Shh
{
	class SourceUsage //枚举值以D3D11_USAGE为参考
	{	
		__Declare_Enum
		{
			Default = 0,		//可以被GPU读和写
			Immutable = 1,	//创建之后就不能被改变
			Dynamic = 2,		//CPU写，GPU读（动态数据）
			Staging = 3		//支持把数据由GPU拷贝到CPU
		};
		__Declare_Enum_Struct(SourceUsage, 0);
	};
	class IndexBufferFormat//枚举值以DXGI_FORMAT为参考
	{		
		__Declare_Enum
		{
			Unknown = 0,
			Index32 = 42,// DXGI_FORMAT_R32_UINT = 42,
			Index16 = 57,//DXGI_FORMAT_R16_UINT = 57
		};
		__Declare_Enum_Struct(IndexBufferFormat, 0);
	public:
		inline size_t getSize() const
		{
			return getSize(*this);
		}
		static size_t getSize(const IndexBufferFormat& format);
		size_t getIndexCount(const IndexBufferFormat& format, size_t sizeInBytes);
	};
	class ShaderSematic
	{
		__Declare_Enum
		{
			POSITION       = 0,
			BLENDWEIGHT    = 1,
			BLENDINDICES   = 2,
			NORMAL         = 3,
			PSIZE          = 4,
			TEXCOORD       = 5,
			TANGENT        = 6,
			BINORMAL       = 7,
			TESSFACTOR     = 8,
			POSITIONT      = 9,
			COLOR          = 10,
			FOG            = 11,
			DEPTH          = 12,
			SAMPLE         = 13,
			COUNT
		};
		__Declare_Enum_Struct(ShaderSematic, 0)
	};

	class _Shh_Export InputElementFormat
	{
		__Declare_Enum
		{
			Float,      //> one-component float
			Float2,     //> two-component float
			Float3,     //> three-component float
			Float4,     //> four-component float
			UByte4,     //> four-component unsigned byte
			Short2,     //> two-component signed short
			Short4,     //> four-component signed short
			ColorBGRA,	//> color type. for D3D9 fix function support
			ColorRGBA,	//> color type. for opengl fix function support
		};
		__Declare_Enum_Struct(InputElementFormat, 0)
	public:
		inline size_t getSize() const
		{
			return getSize(*this);
		}
		static size_t getSize(const InputElementFormat& format);
	};

	class _Shh_Export PrimitieTopology
	{
		__Declare_Enum
		{
			Unknown = 0,
			PointList	= 1,
			LineList	= 2,
			LineStrip	= 3,
			TriangleList	= 4,
			TriangleStrip	= 5,
		};
		__Declare_Enum_Struct(PrimitieTopology, 0);
	};



	//enum InputLayoutCode  //枚举值和D3D11_INPUT_CLASSIFICATION一样
	//{
	//	ILT_VERTEX_DATA     = 0,
	//	ILT_INSTANCE_DATA   = 1 
	//};

	enum TextureCode //D3D11_RESOURCE_DIMENSION为参考
	{
		RT_UNKNOWN	= 0,
		RT_BUFFER	= 1,
		RT_TEX1D	= 2,
		RT_TEX2D	= 3,
		RT_TEX3D	= 4,
		RT_TEXCUBE	= 5
	};

	enum DrawDrvCode
	{
		DrawDrv_Unknown,
		DrawDrv_D3D9,
		DrawDrv_D3D11,
		DrawDrv_GL,
		DrawDrv_GLES,
	};
	class _Shh_Export DRV_DESC
	{
	public:
		DRV_DESC();
		size_t width;
		size_t height;
		size_t handle;
		bool full_screen;
		bool stencil_buffer;
	};
	inline DRV_DESC::DRV_DESC()
		: width(0)
		, height(0)
		, handle(0)
		, full_screen(false)
		, stencil_buffer(true)
	{

	}

	class _Shh_Export CompileMessage
	{
	public:

		U8String Title;
		U8String Message;
		int LineOn;
		int Position;
		inline CompileMessage()
			:LineOn(0)
			,Position(0)
		{

		}
	};
	typedef std::vector<CompileMessage> CompileMessageList;
}