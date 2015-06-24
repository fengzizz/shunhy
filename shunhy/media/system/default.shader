shader "default"
{
	SHADER_CODE_BEGIN
	{
	
			SurfaceOut surface(SurfaceIn sfin)
			{
				SurfaceOut sfout = (SurfaceOut)0;
				sfout.Color = float4(0.8,0.8,0.8,0.8);
				return sfout;
			}	
			
	}SHADER_CODE_END
	
	technique "normal"
	{
		pass "pass0"
		{
			property
			{
					surface = surface
			}
		}
	}
}
