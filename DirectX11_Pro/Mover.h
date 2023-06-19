#pragma once

#include "common.h"
#include "CollisionTag.h"
#include "Collision.h"

using namespace DirectX;
using namespace Tag;

class Mover
{
public:
	Mover();
	virtual ~Mover();

	virtual void Initialize();

	// ゲッター
	const XMFLOAT3 GetPos() const { return param.pos; };
	const CollisionTag GetTag() const { return param.tag; };
	const bool GetExist() const { return exist; };

protected:
	// オブジェクトのパラメータ
	struct Param
	{
		XMFLOAT3 pos;			// 現在の座標（実際の描画位置）
		XMFLOAT3 prevPos;		// 1フレーム前の座標
		XMFLOAT3 nextPos;		// １フレーム後の座標（次の描画位置）
		XMFLOAT3 dir;
		Collision* collision;
		CollisionTag tag;
	};

	//class DeltaTime& deltaTime;

	Param param;
	//float deltaTime;	// デルタタイム
	bool exist;			// 存在するか

	void ModifyingPosition();		// 位置を修正する
	void MoveFinish();				// 実際にモデルを移動させる
private:
};

