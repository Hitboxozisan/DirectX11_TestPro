#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class FireSpark
{
public:
	FireSpark();
	~FireSpark();

	void Init(int MaxParticle, XMFLOAT3& EmitPos);
	void Run();
	XMFLOAT3& GetParticlePos(int index);

private:

	struct Part
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Dir;
		float Speed;
		int BirthFrame;

		Part()
		{
			ZeroMemory(this, sizeof(Part));
		}
	};

	int m_MaxParticle;
	XMFLOAT3 m_EmitPos;
	Part* pPartArray;
	int m_Frame;

};

