shader "test"
{
	SHADER_CODE_BEGIN
	{
	
			SurfaceOut surface(SurfaceIn sfin)
			{
				SurfaceOut sfout = (SurfaceOut)0;
				sfout.Color = sampleDiffuse(sfin.Texcoord);ttx
				return sfout;
			}	
			
	}SHADER_CODE_END
	
	technique "normal"
	{
		pass "pass0"
		{
			property
			{
			//cullMode Nonexxxcc
			}
		}
	}
	
	technique "tta"
	{
		pass "pass0"
		{
			property
			{
					// test.
							
					surface = surface
					cullMode None
					depthbias 0.001
					ZTest On
					ZWrite Off
					blendMode [Add] SRCALPHA INVSRCALPHA
										
					colormask RGB
					alphatest Off
					
					samplerState [_diffuseMap] Wrap Linear		//_diffuseMap			
					
					
					vector [_color] "1, 0.0,0.5f, 1.00"		
			}

		}
		pass
		{
			property
			{
			//surface = surface
			}
		}
		
		pass "nimei"
		{

		}
	}

}
