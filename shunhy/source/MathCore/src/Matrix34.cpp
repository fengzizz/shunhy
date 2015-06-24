#include "Matrix34.h"

namespace Shh
{

	const Matrix34 Matrix34::Zero(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);

	const Matrix34 Matrix34::Identity(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f);

	const int Matrix34::ElementCount = 3 * 4;
	const int Matrix34::ElementSize = sizeof(Single);
	const int Matrix34::SizeInByte = sizeof(Matrix34);
}