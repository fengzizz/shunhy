#include "Quaternion.h"
//#include "OthersDef.h"

namespace Shh
{
	const Quaternion Quaternion::Identity(1.0f, 0.0f, 0.0f, 0.0f);

	const int Quaternion::ElementCount = 4;
	const int Quaternion::ElementSize = sizeof(Single);
	const int Quaternion::SizeInByte = sizeof(Quaternion);
}