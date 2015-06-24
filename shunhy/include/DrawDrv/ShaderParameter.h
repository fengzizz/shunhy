#ifndef __SHADER_PARAMETER_H__
#define __SHADER_PARAMETER_H__
#include <map>
#include "Core/Nameable.h"
#include "MathCore/Matrix4.h"
#include "DrawDrv/RenderState.h"
#include "DrawDrv/DrawDrvDef.h"
namespace Shh
{
	template<typename _Ty>
	class DataParameter : public Nameable
	{
		__Super(Nameable);
	public:
		DataParameter();
		DataParameter(const DataParameter& dp);
		DataParameter(const super::Name& name, const _Ty& data);
		const _Ty& GetData() const;
		void SetData(const _Ty& d);
	private:
		_Ty mData;
	};
	template<typename _Ty>
	inline DataParameter<_Ty>::DataParameter()
	{

	}
	template<typename _Ty>
	inline DataParameter<_Ty>::DataParameter(const DataParameter<_Ty>& dp)
		:super(dp.GetName())
		,mData(dp.mData)
	{

	}
	template<typename _Ty>
	inline DataParameter<_Ty>::DataParameter(const super::Name& name, const _Ty& data)
		:super(name)
		,mData(data)
	{

	}
	template<typename _Ty>
	inline const typename _Ty& DataParameter<_Ty>::GetData() const
	{
		return this->mData;
	}

	template<typename _Ty>
	inline void DataParameter<_Ty>::SetData(const _Ty& d)
	{
		this->mData = d;
	}

	template class _Shh_Export DataParameter<Vector4>;
	template class _Shh_Export DataParameter<Matrix4>;
	template class _Shh_Export DataParameter<SamplerState>;

	typedef DataParameter<Vector4> VectorParameter;

	typedef DataParameter<Matrix4> MatrixParameter;

	typedef DataParameter<SamplerState> TextureSampler;

	//------------------------------------------------------------------------------------------------------------------------------------
	class _Shh_Export ShaderParameters
	{
	public:
		typedef Nameable::Name ParameterName;
		typedef std::map<ParameterName, MatrixParameter> Matrics;
		typedef std::map<ParameterName, VectorParameter> Vectors;
		typedef std::map<ParameterName, TextureSampler> Samplers;
		~ShaderParameters();
		void SetMatrix(const ParameterName& name, const Matrix4& matrix);
		void SetVector(const ParameterName& name, const Vector4& vector);
		void SetSampler(const ParameterName& name, const SamplerState& state);
	private:
		Matrics mMatrics;
		Vectors mVectors;
		Samplers mSamplers;
	};

	inline void ShaderParameters::SetMatrix(const ParameterName& name, const Matrix4& matrix)
	{
		mMatrics[name] = MatrixParameter(name, matrix);
	}
	inline void ShaderParameters::SetVector(const ParameterName& name, const Vector4& vector)
	{
		mVectors[name] = VectorParameter(name, vector);
	}
	inline void ShaderParameters::SetSampler(const ParameterName& name, const SamplerState& state)
	{
		mSamplers[name] = TextureSampler(name, state);
	}
}

#endif //__SHADER_PARAMETER_H__