#include <d3d11shader.h>
#include "MathCore/MatrixDef.h"
#include "MathCore/VectorDef.h"
#include "D3d11_BoundResource.h"
#if __Renderer_d3d11__
namespace Shh
{

	D3d11BoundResource::D3d11BoundResource()
		:mType(SP_UNKNOWN)
	{

	}

	D3d11BoundResource::~D3d11BoundResource()
	{

	}

	void D3d11BoundResource::Set(const HString& name, EShaderParam type)
	{
		mName = name;
		mType = type;
	}

	D3d11BoundValue::D3d11BoundValue()
		:mBuffer(nullptr)
		,mValue(nullptr)
		,mOffset(0)
		,mSize(0)
	{

	}
	D3d11BoundValue::~D3d11BoundValue()
	{
		releaseBoundValue();
	}

	void D3d11BoundValue::SetInfo(const HString& name, EShaderParam type, const D3d11ConstBuffer* buffer, size_t offset, size_t size)
	{
		mName = name;
		mBuffer = buffer;
		mOffset = offset;
		mSize = size;
		releaseBoundValue();
		switch(type)
		{
		case SP_MATRIX44:
			{
				mValue = new bound_value_t<Matrix4>();
				break;
			}
		case SP_FLOAT4:
			{
				mValue = new bound_value_t<Vector4>();
				break;
			}
		case SP_FLOAT3:
			{
				mValue = new bound_value_t<Vector3>();
				break;
			}
		case SP_FLOAT2:
			{
				mValue = new bound_value_t<Vector2>();
				break;
			}
		case SP_FLOAT:
			{
				mValue = new bound_value_t<float>();
				break;
			}
		case SP_INT:
			{
				mValue = new bound_value_t<int>();
				break;
			}
		default:
			{
				shh_warnning("unknown bounding value type(name: %s, type: %d).", name.string().c_str(), (int)type);
				break;
			}
		}

		if (mValue)
		{
			shh_assert(mValue->value_size() == size);
			mValue->set(buffer->GetPtr(offset));
		}
	}

	void D3d11BoundValue::releaseBoundValue()
	{
		if (mValue)
		{
			shh_delete mValue;
			mValue = nullptr;
		}
	}


	D3d11ConstBuffer::D3d11ConstBuffer()
	{

	}

	D3d11ConstBuffer::~D3d11ConstBuffer()
	{

	}
	D3d11BoundTexture::D3d11BoundTexture()
	{

	}

	D3d11BoundTexture::~D3d11BoundTexture()
	{

	}
}
#endif
