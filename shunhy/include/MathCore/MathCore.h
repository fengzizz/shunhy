#include <cmath>
#include "MathCoreDef.h"
namespace Shh
{
	class _Shh_Export Math
	{
	public:
		static int IAbs(int nValue);
		static Single Sin(Single Rad);
		static Single Cos(Single Rad);
		static Single ACos(Single Rad);
		static Single ASin(Single Rad);
		static Single FAbs(Single fValue);
		static Single Sqrt(Single fValue);

		static const Single PI_Div_4;
		static const Single PI_Div_2;
		static const Single PI;
		
	};
	inline int Math::IAbs(int nValue)
	{
		return std::abs(nValue);
	}
	inline Single Math::FAbs(Single fValue)
	{
		return (fValue > 0.0f) ? fValue : -fValue;
	}
	inline Single Math::Sin(Single Rad)
	{
		return sin(Rad);
	}
	inline Single Math::Cos(Single Rad)
	{
		return cos(Rad);
	}
	inline Single Math::ASin(Single Rad)
	{
		return asin(Rad);
	}
	inline Single Math::ACos(Single Rad)
	{
		return acos(Rad);
	}
	inline Single Math::Sqrt(Single fValue)
	{
		return sqrt(fValue);
	}
}