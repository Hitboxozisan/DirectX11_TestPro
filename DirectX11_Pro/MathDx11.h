#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

namespace MathDx11
{
	// XMFLOAT3���Z
	XMFLOAT3 operator+(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator*(const XMFLOAT3& lhs, float rhs);
	XMFLOAT3 operator+=(XMFLOAT3& lhs, const XMFLOAT3& rhs);
	XMFLOAT3 operator*=(XMFLOAT3& lhs, float rhs);
	 // ���K��
	XMFLOAT3 NormalizeXMFLOAT3(XMFLOAT3& vec);
	 // ���Z
	XMFLOAT3 SubXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs);
	 // �O��
	XMFLOAT3 CrossXMFLOAT3(const XMFLOAT3& lhs, const XMFLOAT3& rhs);

	// �ϊ�����
	const XMFLOAT3 ConvertXMVECTORFromXMFLOAT3(const XMVECTOR vec);
	const XMVECTOR ConvertXMFLOAT3FromXMVECTOR(const XMFLOAT3 lhs);
	const XMVECTOR ConvertXMFLOAT4FromXMVECTOR(const XMFLOAT4 lhs);
	const XMMATRIX ConvertXMFLOAT3FromXMMATRIX(const XMFLOAT3 lhs);

	const XMFLOAT4 ConversionFloat4(const XMVECTOR lhs);
}