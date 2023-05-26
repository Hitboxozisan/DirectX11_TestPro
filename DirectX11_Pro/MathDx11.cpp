#include "Framework.h"
#include "Common.h"
#include "MathDx11.h"

using namespace DirectX;

namespace MathDx11
{
	/// <summary>
	/// XMFLOAT
	/// </summary>
	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 ret(0.0f, 0.0f, 0.0f);
		ret.x = lhs.x + rhs.x;
		ret.y = lhs.y + rhs.y;
		ret.z = lhs.z + rhs.z;
		return ret;
	}

	XMFLOAT3 operator*(const XMFLOAT3& lhs, float s)
	{
		XMFLOAT3 ret(0.0f, 0.0f, 0.0f);
		ret.x = lhs.x * s;
		ret.y = lhs.y * s;
		ret.z = lhs.z * s;
		return ret;
	}

	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		lhs = lhs + rhs;
		return lhs;
	}

	XMFLOAT3 operator*=(XMFLOAT3& lhs, float rhs)
	{
		lhs = lhs * rhs;
		return lhs;
	}

	/// <summary>
	/// ���K��
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3& vec)
	{
		float scale;
		XMFLOAT3 ret;

		scale = sqrt(pow(vec.x, 2.0f) + pow(vec.y, 2.0f) + pow(vec.z, 2.0f));
		ret.x = vec.x / scale;
		ret.y = vec.y / scale;
		ret.z = vec.z / scale;

		return ret;
	}

	XMFLOAT3 SubXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 ret;
		ret.x = lhs.x - rhs.x;
		ret.x = lhs.x - rhs.x;
		ret.x = lhs.x - rhs.x;

		return ret;
	}

	/// <summary>
	/// XMVECTOR��XMFLOAT�ɕϊ�
	/// </summary>
	/// <param name="vec"></param>
	/// <returns></returns>
	const XMFLOAT3 ConvertXMVECTORFromXMFLOAT3(const XMVECTOR vec)
	{
		XMFLOAT3 ret;
		ret.x = XMVectorGetX(vec);
		ret.y = XMVectorGetY(vec);
		ret.z = XMVectorGetZ(vec);

		return ret;
	}

	/// <summary>
	/// XMFLOAT3��XMVECTOR�ɕϊ�
	/// </summary>
	/// <param name="lhs"></param>
	/// <returns></returns>
	const XMVECTOR ConvertXMFLOAT3FromXMVECTOR(const XMFLOAT3 lhs)
	{
		XMVECTOR ret;
		ret = { lhs.x, lhs.y, lhs.z };

		return ret;
	}

	/// <summary>
	/// XMFLAOT4��XMVECTOR�ɕϊ�
	/// </summary>
	/// <param name="lhs"></param>
	/// <returns></returns>
	const XMVECTOR ConvertXMFLOAT4FromXMVECTOR(const XMFLOAT4 lhs)
	{
		XMVECTOR ret;
		ret = { lhs.x, lhs.y, lhs.z, lhs.w };

		return ret;
	}

	/// <summary>
	/// XMFLOAT3��XMMATRIX�ɕϊ�
	/// </summary>
	/// <param name="lhs"></param>
	/// <returns></returns>
	const XMMATRIX ConvertXMFLOAT3FromXMMATRIX(const XMFLOAT3 lhs)
	{
		XMVECTOR vec = XMVectorSet(lhs.x, lhs.y, lhs.z, 0.0f);
		XMMATRIX ret = XMMatrixTranslationFromVector(vec);

		return ret;
	}


	const XMFLOAT4 ConversionFloat4(const XMVECTOR lhs)
	{
		XMFLOAT4 ret;
		
		return ret;
	}
}