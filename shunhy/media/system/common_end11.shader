

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