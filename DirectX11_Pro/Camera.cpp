#include "Camera.h"
#include "KeyManager.h"
#include "Singleton.h"
#include "MathDx11.h"

using namespace MathDx11;

Camera::Camera()
{
	// �����Ȃ�
}

Camera::~Camera()
{
	// �����Ȃ�
}

/// <summary>
/// ����������
/// </summary>
void Camera::Init()
{	
	cameraPos = { 0.0f, 0.0f, 0.0f };
	yawFlo = 0;
	dir = { 0.0f, 0.0f, 1.0f };
	position = INITIAL_POS;
	upDir = INITIAL_UP_DIR;
}

/// <summary>
/// �X�V����
/// </summary>
void Camera::Update()
{
	MoveCamera();
	RotateCamera();
}

/// <summary>
/// �`�揈��
/// </summary>
void Camera::Render()
{

	// �r���[�g�����X�t�H�[��
	lookPos = position + dir;
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

/// <summary>
/// �J�����𓮂���
/// </summary>
void Camera::MoveCamera()
{
	KeyManager key = KeyManager::GetInstance();

	cameraPos.x += -(key.IsKeyPush(KeyInfo::Left)) * 0.001 + (key.IsKeyPush(KeyInfo::Right)) * 0.001;
	cameraPos.y += -(key.IsKeyPush(KeyInfo::Down)) * 0.001 + (key.IsKeyPush(KeyInfo::Up)) * 0.001;

	// ���ۂ̈ʒu���X�V
	position = ConvertFloat3FromVector(cameraPos);
}

/// <summary>
/// �J��������]������
/// </summary>
void Camera::RotateCamera()
{
	KeyManager key = KeyManager::GetInstance();

	yawFlo += -(key.IsKeyPush(KeyInfo::RotateL)) * 0.01 + (key.IsKeyPush(KeyInfo::RotateR)) * 0.01;

	yaw = XMMatrixRotationY(yawFlo);

	dir = { 0.0f, 0.0f, 1.0f };
	dir = XMVector3TransformCoord(dir, yaw);

}
