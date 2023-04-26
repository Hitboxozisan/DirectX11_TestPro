#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class Light
{
public:

	const XMVECTOR GetLight() const { return m_vLight; }
	const void SetLight(const XMVECTOR inLight);
private:
	XMVECTOR m_vLight;
};

