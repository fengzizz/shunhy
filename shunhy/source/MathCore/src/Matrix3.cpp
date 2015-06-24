#include "Matrix3.h"
#include "Matrix4.h"
#include "Matrix43.h"
namespace Shh
{

	const Matrix3 Matrix3::Zero(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f );

	const Matrix3 Matrix3::Identity(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);

	const int Matrix3::ElementCount = 3 * 3;
	const int Matrix3::ElementSize = sizeof(Single);
	const int Matrix3::SizeInByte = sizeof(Matrix3);
}