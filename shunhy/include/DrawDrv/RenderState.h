

#ifndef __RENDER_STATE_H__
#define __RENDER_STATE_H__
#include "Core/TEnum.h"
#include "DrawDrv/RenderFormat.h"

namespace Shh
{

	class _Shh_Export FillMode
	{
		__Declare_Enum
		{
			Point = 1,
			Wireframe = 2,
			Solid = 3
		};
		__Declare_Enum_Struct_With_Map(FillMode, Point);
	public:
		static bool parse(const U8String& name, FillMode& mode);
	};

	class _Shh_Export CullMode
	{
		__Declare_Enum
		{
			None = 1,
			Front = 2,
			Back = 3
		};
		__Declare_Enum_Struct_With_Map(CullMode, None);
	public:
		static bool parse(const U8String& name, CullMode& mode);
	};

	class _Shh_Export BlendOperation
	{
		__Declare_Enum
		{
			Add = 1,
			Subtract = 2,
			RevSubtract	= 3,
			Min = 4,
			Max = 5,
		};
		__Declare_Enum_Struct_With_Map(BlendOperation, 0);
	public:
		static bool parse(const U8String& name, BlendOperation& operation);
	};

	class _Shh_Export BlendFactor
	{
		__Declare_Enum
		{
			Zero = 1,
			One = 2,
			SrcColor = 3,
			InvSrcColor = 4,		
			SrcAlpha = 5,		
			InvSrcAlpha = 6,
			DestAlpha = 7,
			InvDestAlpha = 8,		
			DestColor = 9,
			InvDestColor = 10,
			SrcAlphaSat = 11,

			BlentFactor = 14,
			InvBlentFactor = 15,
			Src1Color = 16,
			InvSrc1Color = 17,
			Src1Alpha = 18,
			InvSrc1Alpha = 19,
		};
		__Declare_Enum_Struct_With_Map(BlendFactor, 0);
	public:
		static bool parse(const U8String& name, BlendFactor& factor);
	};

	class _Shh_Export ComparisonFunction
	{
		__Declare_Enum
		{
			Nerver = 1,		
			Less = 2,
			Equal = 3,
			LessEqual = 4,
			Grater = 5,
			NotEqual = 6,
			GraterEqual = 7,	
			Always = 8,
		};
		__Declare_Enum_Struct_With_Map(ComparisonFunction, 0);
	public:
		static bool parse(const U8String& name, ComparisonFunction& func);
	};

	class _Shh_Export StencilOperation
	{
		__Declare_Enum
		{
			Keep = 1,
			Zero = 2,
			Replace = 3,
			IncrSat = 4,
			DecrSat = 5,
			Invert = 6,
			Incr = 7,
			Decr = 8,
		};
		__Declare_Enum_Struct_With_Map(StencilOperation, 0);
	public:
		static bool parse(const U8String& name, StencilOperation& op);
	};

	//enum ColorMask
	//{
	//	eCOLORMASKRED   = 1UL << 3,
	//	eCOLORMASKGREEN = 1UL << 2,
	//	eCOLORMASKBLUE  = 1UL << 1,
	//	eCOLORMASKALPHA = 1UL << 0,
	//	eCOLORMASKRGB   = eCOLORMASKRED | eCOLORMASKGREEN | eCOLORMASKBLUE,
	//	eCOLORMASKRGBA   = eCOLORMASKRED | eCOLORMASKGREEN | eCOLORMASKBLUE | eCOLORMASKALPHA
	//};


	class _Shh_Export TextureAddressMode
	{
		__Declare_Enum
		{
			Wrap = 1,
			Mirror = 2,
			Clamp = 3,
			Border = 4,
			MirrorOnce = 5,
		};
		__Declare_Enum_Struct_With_Map(TextureAddressMode, 0);
	public:
		static bool parse(const U8String& name, TextureAddressMode& mode);
	};


	class _Shh_Export TextureFilter
	{
		__Declare_Enum
		{
			Point,
			Linear,
			Anisotropic,
		};
		__Declare_Enum_Struct_With_Map(TextureFilter, 0);
	public:
		static bool parse(const U8String& name, TextureFilter& filter);
	};


	class _Shh_Export ColorWriteMask
	{
		__Declare_Enum
		{
			None = 0,
			Red = 1,
			Green = 2,
			Blue = 4,
			Alpha = 8,
			RGB = Red | Green | Blue,
			All = Red | Green | Blue | Alpha
		};
		__Declare_Enum_Struct(ColorWriteMask, None);
	public:
		static bool parse(const U8String& name, ColorWriteMask& mark);
	};

	struct _Shh_Export DeviceRasterizerState
	{
		FillMode			fillMode;
		CullMode			cullMode;
		float				depthBias;

		float				slopScaleDepthBias;//保留
		bool				scissorTestEnable;//保留
		bool				multisampleEnable;//保留

		DeviceRasterizerState();
	};

	struct _Shh_Export DeviceDepthAndStencilState
	{
		ComparisonFunction	depthFunc;
		
		ComparisonFunction	stencilFunc;
		StencilOperation	stencilFail;
		StencilOperation	stencilZFail;
		StencilOperation	stencilPass;

		ComparisonFunction	stencilBackFunc;
		StencilOperation	stencilBackFail;
		StencilOperation	stencilBackZFail;
		StencilOperation	stencilBackPass;

		uint8               stencilRef;
		uint8				stencilReadMask;
		uint8				stencilWriteMask;

		bool				depthTestEnable;
		bool				depthWriteEnable;
		bool				stencilEnable;

		bool				stencilBackCustom;

		DeviceDepthAndStencilState();
	};

	struct _Shh_Export DeviceTargetBlendState
	{

		BlendOperation		blendOP;
		BlendFactor			srcBlend;
		BlendFactor			destBlend;

		BlendOperation		blendOPAlpha;//保留
		BlendFactor			srcBlendAlpha;//保留
		BlendFactor			destBlendAlpha;//保留

		ColorWriteMask		colorWriteMask;

		bool				alphaBlendEnable;
		DeviceTargetBlendState();
	};

	struct _Shh_Export DeviceBlendState
	{
		ComparisonFunction		alphaFunc;
		float					alphaRef;
		bool					alphaTestEnable;
		bool					separateAlphaBlendEnable;//保留
		std::vector<DeviceTargetBlendState> targets;
		DeviceBlendState();
	};

	struct _Shh_Export SamplerState
	{

		TextureAddressMode	addressU;
		TextureAddressMode	addressV;
		TextureAddressMode	addressW;
		TextureCode		textureType;
		TextureFilter		Filter;
		uint				maxAnisotropy;
		bool				textureIndexEnable;

		SamplerState();
	};

	struct _Shh_Export DeviceSamplerState
	{
		std::vector<SamplerState> samplers;
	};
}

#endif //__RENDER_STATE_H__
