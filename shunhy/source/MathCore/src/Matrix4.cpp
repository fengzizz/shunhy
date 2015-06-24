#include "Matrix4.h"
#include "Matrix4.h"
namespace Shh
{

	const Matrix4 Matrix4::Zero(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f );

	const Matrix4 Matrix4::Identity(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f );

	const Matrix4 Matrix4::ClipSpace2DToImageSpace(
		0.5f,  0.0f, 0.0f, 0.5f, 
		0.0f, -0.5f, 0.0f, 0.5f, 
		0.0f,  0.0f, 1.0f, 0.0f,
		0.0f,  0.0f, 0.0f, 1.0f);

	const int Matrix4::ElementCount = 4 * 4;
	const int Matrix4::ElementSize = sizeof(Single);
	const int Matrix4::SizeInByte = sizeof(Matrix4);
}