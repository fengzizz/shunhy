#pragma once

#include "Core/CoreDef.h"
#include "Core/IRelease.h"
#include "Core/U8String.h"
#include "DrawDrv/DrawDrvDef.h"
namespace Shh
{
	enum SourceUsage //枚举值以D3D11_USAGE为参考
	{

		//		D3D11_USAGE_DEFAULT     = 0,
		//		D3D11_USAGE_IMMUTABLE   = 1,
		//		D3D11_USAGE_DYNAMIC     = 2,
		//		D3D11_USAGE_STAGING     = 3,	
		BufferUsageDefault = 0,		//可以被GPU读和写
		BufferUsageImmutable = 1,	//创建之后就不能被改变
		BufferUsageDynamic = 2,		//CPU写，GPU读（动态数据）
		BufferUsageStaging = 3		//支持把数据由GPU拷贝到CPU
	};
	enum IndexBufferFormat//枚举值以DXGI_FORMAT为参考
	{		
		IBF_UINT32 = 42,// DXGI_FORMAT_R32_UINT = 42,
		IBF_UINT16 = 57,//DXGI_FORMAT_R16_UINT = 57
	};
	enum ShaderSematic
	{
		SS_POSITION       = 0,
		SS_BLENDWEIGHT    = 1,
		SS_BLENDINDICES   = 2,
		SS_NORMAL         = 3,
		SS_PSIZE          = 4,
		SS_TEXCOORD       = 5,
		SS_TANGENT        = 6,
		SS_BINORMAL       = 7,
		SS_TESSFACTOR     = 8,
		SS_POSITIONT      = 9,
		SS_COLOR          = 10,
		SS_FOG            = 11,
		SS_DEPTH          = 12,
		SS_SAMPLE         = 13,
		SS_COUNT
	};
	enum InputFormat//枚举值以DXGI_FORMAT为参考
	{
		IF_UNKNOWN                      = 0,
		IF_X32Y32Z32A32_TYPELESS        = 1,
		IF_X32Y32Z32A32_FLOAT           = 2,
		IF_X32Y32Z32A32_UINT            = 3,
		IF_X32Y32Z32A32_SINT            = 4,

		IF_X32Y32Z32_TYPELESS           = 5,
		IF_X32Y32Z32_FLOAT              = 6,
		IF_X32Y32Z32_UINT               = 7,
		IF_X32Y32Z32_SINT               = 8,


		IF_X32Y32_TYPELESS              = 15,
		IF_X32Y32_FLOAT                 = 16,
		IF_X32Y32_UINT                  = 17,
		IF_X32Y32_SINT                  = 18,

		IF_X32_TYPELESS                 = 39,
		//IF_D32_FLOAT                    = 40,
		IF_X32_FLOAT                    = 41,
		IF_X32_UINT                     = 42,
		IF_X32_SINT                     = 43,

		IF_X8Y8Z8W8_TYPELESS            = 27,
		IF_X8Y8Z8W8_UNORM               = 28,
		IF_X8Y8Z8W8_UNORM_SRGB          = 29,
		IF_X8Y8Z8W8_UINT                = 30,
		IF_X8Y8Z8W8_SNORM               = 31,
		IF_X8Y8Z8W8_SINT                = 32,

	};

	enum InputLayoutType  //枚举值和D3D11_INPUT_CLASSIFICATION一样
	{
		TLT_VERTEX_DATA     = 0,
		TLT_INSTANCE_DATA   = 1 
	};

	enum ResourceType //D3D11_RESOURCE_DIMENSION为参考
	{
		RT_UNKNOWN	= 0,
		RT_BUFFER	= 1,
		RT_TEX1D	= 2,
		RT_TEX2D	= 3,
		RT_TEX3D	= 4,
		RT_TEXCUBE	= 5
	};

	enum DrawDrvType
	{
		DrawDrv_Unknown,
		DrawDrv_D3D9,
		DrawDrv_D3D11,
		DrawDrv_GL,
		DrawDrv_GLES,
	};
	class DRV_DESC
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

	inline size_t GetIndexCount(IndexBufferFormat format, size_t sizeInBytes)
	{
		switch(format)
		{
		case IBF_UINT16:
			{
				return sizeInBytes / 2;
			}
		case IBF_UINT32:
			{
				return sizeInBytes / 4;
			}
		default:
			{
				break;
			}
		}
		return Invalid_Count;
	}
}