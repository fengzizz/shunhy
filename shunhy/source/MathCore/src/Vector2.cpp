#include "Vector2.h"

namespace Shh
{
	const Vector2 Vector2::Zero(0.0f, 0.0f);
	const Vector2 Vector2::Unit_X(1.0f, 0.0f);
	const Vector2 Vector2::Unit_Y(0.0f, 1.0f);
	const Vector2 Vector2::One(1.0f, 1.0f);

	const int Vector2::ElementCount = 2;
	const int Vector2::ElementSize = sizeof(Single);
	const int Vector2::SizeInByte = sizeof(Vector2);
}