#include "Camera.h"
#include "KeyManager.h"
#include "Singleton.h"
#include "MathDx11.h"

using namespace MathDx11;

Camera::Camera()
{
	// 処理なし
}

Camera::~Camera()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
void Camera::Init()
{	
	cameraPos = { 0.0f, 0.0f, 0.0f };
	yawFlo = 0;
	zoom = 4;
	dir = { 0.0f, 0.0f, 1.0f };
	position = INITIAL_POS;
	upDir = INITIAL_UP_DIR;
}

/// <summary>
/// 更新処理
/// </summary>
void Camera::Update()
{
	MoveCamera();
	RotateCamera();
	ZoomInOut();
}

/// <summary>
/// 描画処理
/// </summary>
void Camera::Render()
{

	// ビュートランスフォーム
	lookPos = position + dir;
	view = XMMatrixLookAtLH(position, lookPos, upDir);

	proj = XMMatrixPerspectiveFovLH(XM_PI / zoom, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);
}

/// <summary>
/// カメラを動かす
/// </summary>
void Camera::MoveCamera()
{
	KeyManager key = KeyManager::GetInstance();

	cameraPos.x += -(key.IsKeyPush(KeyInfo::Left)) * 0.001 + (key.IsKeyPush(KeyInfo::Right)) * 0.001;
	cameraPos.y += -(key.IsKeyPush(KeyInfo::Down)) * 0.001 + (key.IsKeyPush(KeyInfo::Up)) * 0.001;

	// 実際の位置を更新
	position = ConvertFloat3FromVector(cameraPos);
}

/// <summary>
/// カメラを回転させる
/// </summary>
void Camera::RotateCamera()
{
	KeyManager key = KeyManager::GetInstance();

	yawFlo += -(key.IsKeyPush(KeyInfo::RotateL)) * 0.01 + (key.IsKeyPush(KeyInfo::RotateR)) * 0.01;

	yaw = XMMatrixRotationY(yawFlo);

	dir = { 0.0f, 0.0f, 1.0f };
	dir = XMVector3TransformCoord(dir, yaw);

}

/// <summary>
/// ズームイン・アウト
/// </summary>
void Camera::ZoomInOut()
{
	KeyManager key = KeyManager::GetInstance();
	zoom += (key.IsKeyPush(KeyInfo::ZoomIn)) * 0.03 - (key.IsKeyPush(KeyInfo::ZoomOut)) * 0.03;
	if (zoom < 1.1)
	{
		zoom = 1.1;
	}
	if (zoom > 30)
	{
		zoom = 30;
	}
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