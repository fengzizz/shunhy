//--------------------------------------------------------------------------------------
// Globals
//--------------------------------------------------------------------------------------
cbuffer cbCameraParamter// : register( b0 )
{
	matrix		gView	;//: packoffset( c0 );
	matrix		gProj	;//: packoffset( c4 );
//	matrix		gTest_matrix	;//: packoffset( c4 );
//	float3		gTest_float3;
//	float4		gTest_float4;
//	float2		gTest_float2;
//	float2		gTest_float2_1;
//	float4		gTest_float4_1;
};

cbuffer cbObjectParamter// : register( b1 )
{
	matrix		gWorld ;//: packoffset( c0 );
};

cbuffer cbTestParamter// : register( b0 )
{
	matrix		TestgView	;//: packoffset( c0 );
	float4		Test_float4;
	float3		Test_float3;
	float2		Test_float2;
	float			Test_float;
	float4		Test_float4ss[50];
	int				Test_int;

};

//--------------------------------------------------------------------------------------
// Textures and Samplers
//--------------------------------------------------------------------------------------
Texture2D	gDiffuse ;//: register( t0 );
SamplerState gDiffuseSampler ;//: register( s0 );

//--------------------------------------------------------------------------------------
// Input / Output structures
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float4 vPosition	: POSITION;
	float3 vNormal		: NORMAL;
	float2 vTexcoord	: TEXCOORD0;
};
struct VS_OUTPUT
{
	float3 vNormal		: NORMAL;
	float2 vTexcoord	: TEXCOORD0;
	float4 vPosition	: SV_POSITION;
};


struct PS_INPUT
{
    float2 vTexcoord : TEXCOORD0;
    float3 vNormal	: TEXCOORD1;
};

struct PS_OUTPUT
{
    float4 vColor:SV_TARGET;
};

struct SurfaceIn
{
	float2 Texcoord;
	float3 Normal;
};
struct SurfaceOut
{
	float4 Color;
};

float4 sampleDiffuse(float2 texcoord)
{
	return gDiffuse.Sample( gDiffuseSampler, texcoord );
}

