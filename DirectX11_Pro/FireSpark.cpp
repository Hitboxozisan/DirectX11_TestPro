#include "FireSpark.h"
#include "MathDx11.h"

using namespace MathDx11;

FireSpark::FireSpark()
{
	// 処理なし
}

FireSpark::~FireSpark()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void FireSpark::Init(int MaxParticle, XMFLOAT3& EmitPos)
{
	ZeroMemory(this, sizeof(FireSpark));
	m_MaxParticle = MaxParticle;
	m_EmitPos = EmitPos;
	pPartArray = new Part[m_MaxParticle];

	for (int i = 0; i < m_MaxParticle; i++)
	{
		pPartArray[i].Pos = EmitPos;
		pPartArray[i].Dir = XMFLOAT3( 2 * ((float)rand() / (float)RAND_MAX) - 1, (float)rand() / (float)RAND_MAX, 2 * ((float)rand() / (float)RAND_MAX) - 1 );
		pPartArray[i].Dir = XMNormalizeFloat3(pPartArray[i].Dir);
		pPartArray[i].Speed = (5 + ((float)rand() / (float)RAND_MAX)) * 0.00001;
		pPartArray[i].BirthFrame = rand();
		
	}
}

/// <summary>
/// 更新処理
/// </summary>
void FireSpark::Run()
{
	m_Frame++;
	for (int i = 0; i < m_MaxParticle; i++)
	{
		if (m_Frame > pPartArray[i].BirthFrame)
		{
			pPartArray[i].Pos += (pPartArray[i].Dir * pPartArray[i].Speed);
			//重力
			pPartArray[i].Dir += XMFLOAT3(0, -0.0000098, 0);
			//地面でのバウンド
			if (pPartArray[i].Pos.y < 0)
			{
				pPartArray[i].Dir.y = -pPartArray[i].Dir.y;
			}
		}
	}
}

/// <summary>
/// パーティクルの位置を返す
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
XMFLOAT3& FireSpark::GetParticlePos(int index)
{
	return pPartArray[index].Pos;
}
