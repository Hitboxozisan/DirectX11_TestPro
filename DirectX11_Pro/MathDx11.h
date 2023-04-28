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
	XMFLOAT3 XMNormalizeFloat3(XMFLOAT3& vec);						// ���K��

	const XMVECTOR ConversionVec(const XMFLOAT4 lhs);
	const XMFLOAT4 ConversionFloat4(const XMVECTOR lhs);
}