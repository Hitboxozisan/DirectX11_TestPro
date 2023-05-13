#include "Camera.h"
#include "KeyManager.h"
#include "Singleton.h"
#include "MathDx11.h"

using namespace MathDx11;

Camera::Camera()
{
}

Camera::~Camera()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void Camera::Init()
{
	position = INITIAL_POS;
	upDir = INITIAL_UP_DIR;
}

/// <summary>
/// 更新処理
/// </summary>
void Camera::Update()
{
	KeyManager key = Singleton<KeyManager>::GetInstance();
	XMFLOAT3 cameraPos = {0.0f, 0.0f, 0.0f};

	/*if (key.IsKeyPush(KeyInfo::Left))
	{
		cameraPos.x += -10;
	}*/
	cameraPos.x += -(key.IsKeyPush(KeyInfo::Left)) * 1 + (key.IsKeyPush(KeyInfo::Right)) * 1;
	cameraPos.y += -(key.IsKeyPush(KeyInfo::Down)) * 1 + (key.IsKeyPush(KeyInfo::Up)) * 1;

	// 実際の位置を更新
	position = ConvertFloat3FromVector(cameraPos);
}

/// <summary>
/// 描画処理
/// </summary>
void Camera::Render()
{
	// ビュートランスフォーム
	lookPos = position + XMVECTOR{ 0.0f, 0.0f, 1.0f };
	view = XMMatrixLookAtLH(position, lookPos, upDir);

	proj = XMMatrixPerspectiveFovLH(XM_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);
}

const XMMATRIX Camera::GetView()
{
	return view;
}

const XMMATRIX Camera::GetProj()
{
	return proj;
}

const XMVECTOR Camera::GetCameraPos()
{
	return position;
}

const XMVECTOR Camera::GetLookPos()
{
	return lookPos;
}

const XMVECTOR Camera::GetUpVec()
{
	return upDir;
}
