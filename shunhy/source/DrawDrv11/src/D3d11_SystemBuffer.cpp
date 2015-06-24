#include "D3d11_SystemBuffer.h"
#include "Core/Memory.h"
#include <algorithm>
#if __Renderer_d3d11__
namespace Shh
{
	D3d11SystemBuffer::D3d11SystemBuffer()
	{

	}


	D3d11SystemBuffer::~D3d11SystemBuffer()
	{

	}

	void D3d11SystemBuffer::Setup(ID3D11Device* device)
	{
		mConstBuffers.resize(cb_count);
		// Create the constant buffers
		D3D11_BUFFER_DESC bd;
		Memory::Zero(&bd, sizeof(bd));

		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		bd.ByteWidth = sizeof(CBufferCamera);
		HRESULT_SUCCEEDED(device->CreateBuffer(&bd, NULL, &mConstBuffers[cb_camera].buffer));
		mConstBuffers[cb_camera].key = ConstBuffer_Camera_Key;

		bd.ByteWidth = sizeof(CBufferObject);
		HRESULT_SUCCEEDED(device->CreateBuffer(&bd, NULL, &mConstBuffers[cb_object].buffer));
		mConstBuffers[cb_object].key = ConstBuffer_Object_Key;
	}

	bool D3d11SystemBuffer::IsSystemConstBuffer(const HString& name) const
	{
		ConstBuffers::const_iterator it = mConstBuffers.begin();
		ConstBuffers::const_iterator end = mConstBuffers.end();
		while(it != end)
		{
			if (it->key == name)
			{
				return true;
			}
			++it;
		}
		return false;
	}

	void D3d11SystemBuffer::UpdateConstBuffer_Camera(const CBufferCamera& buffer, ID3D11DeviceContext* context)
	{
		context->UpdateSubresource( mConstBuffers[cb_camera].buffer, 0, NULL, &buffer, 0, 0 );
	}

	void D3d11SystemBuffer::UpdateConstBuffer_Object(const CBufferObject& buffer, ID3D11DeviceContext* context)
	{
		context->UpdateSubresource( mConstBuffers[cb_object].buffer, 0, NULL, &buffer, 0, 0 );
	}

	void D3d11SystemBuffer::Release()
	{
		//D3d11Common::DeleteCOMptr(mConstBuffer_Camera.buffer);
		//D3d11Common::DeleteCOMptr(mConstBuffer_Object.buffer);

		std::for_each(mConstBuffers.begin(), mConstBuffers.end(), [](_sys_const_buffer& x) {
			D3d11Common::DeleteCOMptr(x.buffer);
		});
		mConstBuffers.clear();
	}
}
#endif
