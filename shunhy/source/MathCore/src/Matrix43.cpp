#include "Matrix43.h"

namespace Shh
{

	const Matrix43 Matrix43::Zero(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f);

	const Matrix43 Matrix43::Identity(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f);


	const int Matrix43::ElementCount = 4 * 3;
	const int Matrix43::ElementSize = sizeof(Single);
	const int Matrix43::SizeInByte = sizeof(Matrix43);

}