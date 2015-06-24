#ifndef __D3D11_SYSTEMCONSTBUFFER_H__
#define __D3D11_SYSTEMCONSTBUFFER_H__
#include "Memory.h"
#include "D3d11_Common.h"
#include "ConstBuffer.h"
#include "Core/HString.h"
#include <vector>
namespace Shh
{
#define ConstBuffer_Camera_Key "cbCameraParamter"
#define ConstBuffer_Object_Key "cbObjectParamter"
	class D3d11SystemBuffer final
	{
	public:
		D3d11SystemBuffer();
		~D3d11SystemBuffer();
		bool IsSystemConstBuffer(const HString& name) const;


		bool IsSystemTextureBuffer(const HString& name)
		{
			shh_assert(0);
			return false;
		}

		void Setup(ID3D11Device* device);
		void UpdateConstBuffer_Camera(const CBufferCamera& buffer, ID3D11DeviceContext* context);
		void UpdateConstBuffer_Object(const CBufferObject& buffer, ID3D11DeviceContext* context);
		void Release();
	private:

		struct _sys_const_buffer
		{
			ID3D11Buffer* buffer;
			HString key;
			_sys_const_buffer()
				:buffer(nullptr)
			{

			}
		};
		struct _sys_shader_resource
		{
			String key;
			_sys_shader_resource()
			{

			}
		};
		enum _e_sys_const_buffer
		{
			cb_camera,
			cb_object,
			cb_count
		};
		typedef std::vector<_sys_const_buffer> ConstBuffers;
		ConstBuffers mConstBuffers;
	};
}

#endif //__D3D11_SYSTEMCONSTBUFFER_H__