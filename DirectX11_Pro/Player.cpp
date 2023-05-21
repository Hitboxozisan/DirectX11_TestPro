#include "Player.h"
#include "Singleton.h"
#include "MathDx11.h"
#include "Camera.h"
#include "KeyManager.h"

using namespace MathDx11;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	:key(Singleton<KeyManager>::GetInstance())
	,camera(Singleton<Camera>::GetInstance())
	,isAlive(true)
{
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// 各種終了処理実行
	Fainalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Init()
{
	param.pos = INITIAL_POS;
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Fainalize()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	//Move();
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
}

/// <summary>
/// 当たり判定形状
/// </summary>
/// <param name="other"></param>
void Player::OnCollisionEnter(Collision* other)
{
}

void Player::Move()
{
	// 前方向ベクトルを出す
	XMFLOAT3 Forward = SubXMFLOAT3(param.pos, camera.GetPos());
	// 床にめり込んだりするのを防ぐためY軸は0にする
	Forward.y = 0;

}
