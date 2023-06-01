#include <DirectXMath.h>
#include "Camera.h"
#include "KeyManager.h"
#include "Singleton.h"
#include "MathDx11.h"
//#include "Text.h"

using namespace MathDx11;

Camera::Camera()
	:key(Singleton<KeyManager>::GetInstance())
	//,text(Singleton<Text>::GetInstance())
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
	// ����p���W
	cameraPos = { 0.0f, 5.0f, -4.0f };
	yawFlo = 0;
	zoom = 4;
	dir = { 0.0f, 0.0f, 1.0f };
	// �`��p���W
	//position = INITIAL_POS;
	upDir = INITIAL_UP_DIR;
}

/// <summary>
/// �X�V����
/// </summary>
void Camera::Update()
{
	MoveCamera();
	RotateCamera();
	ZoomInOut();
}

/// <summary>
/// �`�揈��
/// </summary>
void Camera::Render()
{

	// �r���[�g�����X�t�H�[��
	//lookPos = position + dir;
	// �����ʒu�͂�������v���C���[�̏����ʒu��
	lookPos = { 0.0f, 0.0f, 0.0f, 1.0f };
	view = XMMatrixLookAtLH(position, lookPos, upDir);

	proj = XMMatrixPerspectiveFovLH(XM_PI / zoom, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);
}

/// <summary>
/// �J�����𓮂���
/// </summary>
void Camera::MoveCamera()
{
	cameraPos.x += -(key.IsKeyPush(KeyInfo::Left)) * 0.01 + (key.IsKeyPush(KeyInfo::Right)) * 0.01;
	cameraPos.y += -(key.IsKeyPush(KeyInfo::Down)) * 0.01 + (key.IsKeyPush(KeyInfo::Up)) * 0.01;

	// ���ۂ̈ʒu���X�V
	// xmfloat3��xmvector�ɕϊ�
	position = ConvertXMFLOAT3FromXMVECTOR(cameraPos);
}

/// <summary>
/// �J��������]������
/// </summary>
void Camera::RotateCamera()
{
	yawFlo += -(key.IsKeyPush(KeyInfo::RotateL)) * 0.05 + (key.IsKeyPush(KeyInfo::RotateR)) * 0.05;
	pitchFlo += -(key.IsKeyPush(KeyInfo::RotateW)) * 0.05 + (key.IsKeyPush(KeyInfo::RotateS)) * 0.05;

	yaw = XMMatrixRotationY(yawFlo);
	pitch = XMMatrixRotationX(pitchFlo);
	

	dir = { 0.0f, 0.0f, 1.0f };
	dir = XMVector3TransformCoord(dir, yaw);

}

/// <summary>
/// �Y�[���C���E�A�E�g
/// </summary>
void Camera::ZoomInOut()
{
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

const XMFLOAT3 Camera::GetPos()
{
	XMFLOAT3 pos;
	XMStoreFloat3(&pos, position);
	return pos;
}
