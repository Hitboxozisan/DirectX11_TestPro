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
	/// ê≥ãKâª
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

	/// <summary>
	/// å∏éZ
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	XMFLOAT3 SubXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 ret;
		ret.x = lhs.x - rhs.x;
		ret.y = lhs.y - rhs.y;
		ret.z = lhs.z - rhs.z;

		return ret;
	}

	/// <summary>
	/// èÊéZ
	/// </summary>
	/// <param name="vec"></param>
	/// <param name="scale"></param>
	/// <returns></returns>
	XMFLOAT3 ScaleXMFLOAT3(XMFLOAT3& vec, float scale)
	{
		XMFLOAT3 ret = vec;
		ret.x *= scale;
		ret.y *= scale;
		ret.z *= scale;

		return ret;
	}

	/// <summary>
	/// äOêœ
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	XMFLOAT3 CrossXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs)
	{
		XMFLOAT3 vec1 = lhs;
		XMFLOAT3 vec2 = rhs;

		XMVECTOR cross = XMVector3Cross(XMLoadFloat3(&vec1), XMLoadFloat3(&vec2));

		XMFLOAT3 result;
		XMStoreFloat3(&result, cross);

		return result;
	}

	bool operator!=(const XMFLOAT2&& lhs, const XMFLOAT2& rhs)
	{
		if (lhs.x != rhs.x ||
			lhs.y != rhs.y)
		{
			return true;
		}

		return false;
	}

	/// <summary>
	/// XMVECTORÇXMFLOATÇ…ïœä∑
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
	/// XMFLOAT3ÇXMVECTORÇ…ïœä∑
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
	/// XMFLAOT4ÇXMVECTORÇ…ïœä∑
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
	/// XMFLOAT3ÇXMMATRIXÇ…ïœä∑
	/// </summary>
	/// <param name="lhs"></param>
	/// <returns></returns>
	const XMMATRIX ConvertXMFLOAT3FromXMMATRIX(const XMFLOAT3 lhs)
	{
		// ãåéÆ
		//XMVECTOR vec = XMVectorSet(lhs.x, lhs.y, lhs.z, 0.0f);
		//XMMATRIX ret = XMMatrixTranslationFromVector(vec);

		XMMATRIX ret = XMMatrixSet(
			lhs.x, 0.0f, 0.0f, 0.0f,
			0.0f, lhs.y, 0.0f, 0.0f,
			0.0f, 0.0f, lhs.z, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		);

		return ret;
	}


	const XMFLOAT4 ConversionFloat4(const XMVECTOR lhs)
	{
		XMFLOAT4 ret;
		
		return ret;
	}
}