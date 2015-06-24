shader "mesh_diffuse"
{
	program
	{
			SurfaceOut surface(SurfaceIn sfin)
			{
				SurfaceOut sfout = (SurfaceOut)0;
				sfout.Color = sampleDiffuse(sfin.Texcoord);
				return sfout;
			}	
	}
	
	technque "normal"
	{
		pass "pass0"
		{
			surface = surface
		}
	}

}
