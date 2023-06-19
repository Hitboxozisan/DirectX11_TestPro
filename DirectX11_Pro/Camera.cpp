#include <DirectXMath.h>
#include "Camera.h"
#include "KeyManager.h"
#include "Singleton.h"
#include "MathDx11.h"
//#include "Text.h"

using namespace MathDx11;
// �L�[�����o���Ɏg�p
using namespace KeyMgrInfo;

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
	cameraPos = { 0.0f, 5.0f, -10.0f };
	lookPos = { 0.0f, 1.5f, 0.0f };
	upDir = INITIAL_UP_DIR;
	yawFlo = 0;
	zoom = 4;
	dir = { 0.0f, 0.0f, 1.0f };
	// �`��p���W
	position = INITIAL_POS;
}

/// <summary>
/// �X�V����
/// </summary>
void Camera::Update()
{
	//MoveCamera();
	//RotateCamera();
	ZoomInOut();
}

/// <summary>
/// �`�揈��
/// </summary>
void Camera::Render()
{
	upDir = { 0.0f, 1.0f, 0.0f };

	position = ConvertXMFLOAT3FromXMVECTOR(cameraPos);
	
	view = XMMatrixLookAtLH(position, lookPos, upDir);
	
	proj = XMMatrixPerspectiveFovLH(XM_PI / zoom, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);
}

/// <summary>
/// �J�����𓮂���
/// </summary>
void Camera::MoveCamera()
{
	// �L�[�{�[�h
	//cameraPos.x += -(key.IsKeyPush(KeyInfo::KeyLeft)) * 0.01 + (key.IsKeyPush(KeyInfo::KeyRight)) * 0.01;
	//cameraPos.y += -(key.IsKeyPush(KeyInfo::KeyDown)) * 0.01 + (key.IsKeyPush(KeyInfo::KeyUp)) * 0.01;

	// �R���g���[���[
	//cameraPos.x += -(key.IsButtonPush(ButtonInfo::ButtonLeft)) * 0.01 + (key.IsButtonPush(ButtonInfo::ButtonRight)) * 0.01;
	//cameraPos.y += -(key.IsButtonPush(ButtonInfo::ButtonDown)) * 0.01 + (key.IsButtonPush(ButtonInfo::ButtonUp)) * 0.01;

	// ���ۂ̈ʒu���X�V
	// xmfloat3��xmvector�ɕϊ�
	//position = ConvertXMFLOAT3FromXMVECTOR(cameraPos);
}

/// <summary>
/// �J��������]������
/// </summary>
void Camera::RotateCamera()
{
	yawFlo += -(key.IsKeyPush(KeyInfo::KeyRotateL)) * 0.05 + (key.IsKeyPush(KeyInfo::KeyRotateR)) * 0.05;
	//pitchFlo += -(key.IsKeyPush(KeyInfo::KeyRotateW)) * 0.05 + (key.IsKeyPush(KeyInfo::KeyRotateS)) * 0.05;

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
	zoom += (key.IsKeyPush(KeyInfo::KeyZoomIn)) * 0.03 - (key.IsKeyPush(KeyInfo::KeyZoomOut)) * 0.03;
	if (zoom < 1.1)
	{
		zoom = 1.1;
	}
	if (zoom > 30)
	{
		zoom = 30;
	}
}

void Camera::FollowUpPlayer(XMFLOAT3 pos)
{
	cameraPos = pos;
	cameraPos.y += ADJUST_POS_Y;
	cameraPos.z += ADJUST_POS_Z;

	lookPos = XMLoadFloat3(&pos);
	position = ConvertXMFLOAT3FromXMVECTOR(cameraPos);
}

const XMFLOAT3 Camera::GetPos()
{
	XMFLOAT3 pos;
	XMStoreFloat3(&pos, position);
	return pos;
}
