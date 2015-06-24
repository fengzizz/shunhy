#include "Vector3.h"

namespace Shh
{
	const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Unit_X(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::Unit_Y(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::Unit_Z(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::One(1.0f, 1.0f, 1.0f);

	const int Vector3::ElementCount = 3;
	const int Vector3::ElementSize = sizeof(Single);
	const int Vector3::SizeInByte = sizeof(Vector3);
}