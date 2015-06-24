#include "Mouse.h"

namespace Shh
{
	Mouse::Mouse()
	{

	}
	Mouse::~Mouse()
	{
	}
	const MouseState& Mouse::GetMouseState() const
	{
		return mMouseState;
	}
}