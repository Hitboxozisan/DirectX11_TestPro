#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

namespace MathDx11
{
	const XMVECTOR ConversionVec(const XMFLOAT4 lhs);
	const XMFLOAT4 ConversionFloat4(const XMVECTOR lhs);
}