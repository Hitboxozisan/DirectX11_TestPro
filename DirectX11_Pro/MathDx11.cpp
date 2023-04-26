#include "Framework.h"
#include "Common.h"

using namespace DirectX;

namespace MathDx11
{
	const XMVECTOR Conversion(const XMFLOAT4 lhs)
	{
		XMVECTOR ret;
		ret = { lhs.x, lhs.y, lhs.z, lhs.w };

		return ret;
	}

	const XMFLOAT4 ConversionFloat4(const XMVECTOR lhs)
	{
		XMFLOAT4 ret;
		
		return ret;
	}
}