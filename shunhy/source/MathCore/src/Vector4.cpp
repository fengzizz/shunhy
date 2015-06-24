#include "Vector4.h"

namespace Shh
{
	const Vector4 Vector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::Unit_X(1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::Unit_Y(0.0f, 1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::Unit_Z(0.0f, 0.0f, 1.0f, 0.0f);
	const Vector4 Vector4::Unit_W(0.0f, 0.0f, 0.0f, 1.0f);
	const Vector4 Vector4::One(1.0f, 1.0f, 1.0f, 1.0f);

	const int Vector4::ElementCount = 4;
	const int Vector4::ElementSize = sizeof(Single);
	const int Vector4::SizeInByte = sizeof(Vector4);
}