#ifndef __D3D11_BOUNDRESOURCE_H__
#define __D3D11_BOUNDRESOURCE_H__
#include "Core/HString.h"
#include "Core/Memory.h"
#include "D3d11_Common.h"
#include "DrawDrv/GPUProgram.h"

struct ID3D11ShaderReflection;
struct _D3D11_SHADER_INPUT_BIND_DESC;
typedef _D3D11_SHADER_INPUT_BIND_DESC D3D11_SHADER_INPUT_BIND_DESC;
namespace Shh
{
	class D3d11BoundResource
	{
	public:
		virtual ~D3d11BoundResource();
		//virtual void Set(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector) override;
		virtual void Set(const HString& name, EShaderParam type);
		const HString& GetName() const;
	protected:
		D3d11BoundResource();
		HString mName;
		EShaderParam mType;
		//int mBindPoint;
	};

	inline const HString& D3d11BoundResource::GetName() const
	{
		return mName;
	}

	class D3d11BoundValue : public D3d11BoundResource
	{
		__Super(D3d11BoundValue);
	public:
		D3d11BoundValue();
		~D3d11BoundValue();
		void SetInfo(const HString& name, EShaderParam type, const D3d11ConstBuffer* buffer, size_t offset, size_t size);
		
	private:
		void releaseBoundValue();
		class bound_value
		{
		public:
			virtual void set(pointer pAddr) = 0;
			virtual size_t value_size() const = 0;
		};
		template<typename _Ty>
		class bound_value_t : public bound_value
		{
		public:
			bound_value_t()
				:_pvalue(nullptr)
			{
			}
			//virtual void Set(const D3D11_SHADER_INPUT_BIND_DESC& bind, ID3D11ShaderReflection* pReflector) override;
			virtual void set(pointer pAddr)
			{
				_pvalue = (_Ty*)pAddr;
			}

			virtual size_t value_size() const
			{
				return sizeof(_Ty);
			}
		protected:
			_Ty* _pvalue;
		};		

		const D3d11ConstBuffer* mBuffer;	
		bound_value* mValue;
		size_t mOffset;
		size_t mSize;

	};

	class D3d11BoundTexture : public D3d11BoundResource
	{
	public:
		D3d11BoundTexture();
		virtual ~D3d11BoundTexture();
	private:
	};

	class D3d11ConstBuffer : public D3d11BoundResource
	{
		__Super(D3d11BoundResource);	
	public:
		D3d11ConstBuffer();
		~D3d11ConstBuffer();
		
		void Resize(size_t size);

		void Resize(size_t size, byte defaultValue);

		pointer GetPtr() const;

		pointer GetPtr(size_t bias) const;

		size_t GetSize() const;
	private:
		MemoryBlock mBlock;
	};

	inline void D3d11ConstBuffer::Resize(size_t size)
	{
		mBlock.Resize(size);
	}

	inline void D3d11ConstBuffer::Resize(size_t size, byte defaultValue)
	{
		mBlock.ResizeDefault(size, defaultValue);
	}

	inline pointer D3d11ConstBuffer::GetPtr() const
	{
		return mBlock.GetPtr();
	}

	inline pointer D3d11ConstBuffer::GetPtr(size_t bias) const
	{
		shh_assert(0 <= bias && bias < mBlock.GetSize());
		return mBlock.GetPtr(bias);
	}

	inline size_t D3d11ConstBuffer::GetSize() const
	{
		return mBlock.GetSize();
	}
}

#endif //__D3D11_BOUNDRESOURCE_H__