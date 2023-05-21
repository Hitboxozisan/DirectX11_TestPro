#pragma once
#include "Common.h"
#include "Framework.h"
#include "Collision.h"
#include "CollisionTag.h"

using namespace DirectX;
using namespace Tag;

class PlayerBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

	// 座標
	const XMFLOAT3 GetPosition() { return param.pos; };
	// 当たり判定タグ
	const CollisionTag GetTag() { return param.tag; };
	// 当たり判定処理
	virtual void OnCollisionEnter(class Collision* other);

	class Collision* GetCollision() { return param.collision; };

protected:
	// プレイヤーのステータス
	struct Param
	{
		XMFLOAT3 pos;
		class Collision* collision;
		CollisionTag tag;
	};

	Param param;
	bool isExist;

	// エフェクト管理クラス

private:

};

