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


	
			SurfaceOut surface(SurfaceIn sfin)
			{
				SurfaceOut sfout = (SurfaceOut)0;
				sfout.Color = sampleDiffuse(sfin.Texcoord);ttx
				return sfout;
			}	
			
	#define SURFACE_BRUSH surface


//#define SURFACE_BRUSH surface

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VSMain( VS_INPUT Input )
{
	VS_OUTPUT Output;
	
	Output.vPosition = mul(gProj, mul(gView, mul(gWorld, Input.vPosition)));
	
	Output.vNormal = normalize(mul( Input.vNormal, (float3x3)gWorld));
	Output.vTexcoord = Input.vTexcoord;
//----------------- for test --------------------------------------------
	Output.vTexcoord.x = Input.vTexcoord.x + TestgView[0] + Test_float4[0] + Test_float3[0] + Test_float2[0] + Test_float + Test_int;
	
	for(int i = 0; i < 10; ++i)
	{
		Output.vTexcoord.x += Test_float4ss[i].x;
	}

	return Output;
}

//-------------------------------------------------------------
// Pixel Shader
//-------------------------------------------------------------
PS_OUTPUT PSMain(PS_INPUT psInput)
{
    PS_OUTPUT Out_ps;
    SurfaceIn sfin;
    sfin.Texcoord = psInput.vTexcoord;
    sfin.Normal = psInput.vNormal;
    
    SurfaceOut sfout = SURFACE_BRUSH(sfin);
    Out_ps.vColor = sfout.Color;
    return Out_ps;
}