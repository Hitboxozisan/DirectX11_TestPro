#pragma once

#include <map>
#include <Xinput.h>

namespace KeyMgrInfo
{

	// �L�[���
	enum KeyInfo
	{
		KeyUp = VK_UP,
		KeyDown = VK_DOWN,
		KeyLeft = VK_LEFT,
		KeyRight = VK_RIGHT,
		KeyRotateR = 'E',
		KeyRotateL = 'Q',
		KeyRotateW = 'W',
		KeyRotateS = 'S',
		KeyZoomIn = 'P',
		KeyZoomOut = 'L',

	};

	// �R���g���[���[�{�^�����
	enum ButtonInfo
	{
		ButtonUp = XINPUT_GAMEPAD_DPAD_UP,				// ���L�[��
		ButtonDown = XINPUT_GAMEPAD_DPAD_DOWN,			// ���L�[��
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT,		// ���L�[�E
		ButtonLeft = XINPUT_GAMEPAD_DPAD_LEFT,			// ���L�[��
		ButtonDecision = XINPUT_GAMEPAD_A,				// ����
		ButtonReturn = XINPUT_GAMEPAD_B,				// �߂�
	};
}

using namespace KeyMgrInfo;

/// <summary>
/// �L�[�̓��͔���
/// </summary>
class KeyManager
{
public:
	void InitController();
	void KeyStateUpdate();						// �L�[����X�V����
	void ButtonStateUpdate();					// �{�^������X�V����
	void StickStateUpdate();

	// �L�[�{�[�h
	const bool IsKeyPush(KeyInfo keycord);
	bool IsKeyJust(KeyInfo keycord);
	bool IsKeyExit(KeyInfo keycord);
	// �R���g���[���[
	 // �{�^��
	const bool IsButtonPush(ButtonInfo inButton);
	bool IsButtonJust(ButtonInfo inButton);
	bool IsButtonExit(ButtonInfo inButton);
	 // �E�g���K�[
	bool IsCheckRTrigger();
	 // ���g���K�[
	bool IsCheckLTrigger();
	
	
private:
	// �O������A�N�Z�X�𐧌�����
	//KeyManager();
	//KeyManager(const KeyManager&);
	//~KeyManager();
	
	// �L�[���z��
	constexpr static KeyInfo keyInfo[] =
	{
		KeyInfo::KeyUp,
		KeyInfo::KeyDown,
		KeyInfo::KeyLeft,
		KeyInfo::KeyRight,
		KeyInfo::KeyRotateR,
		KeyInfo::KeyRotateL,
		KeyInfo::KeyRotateW,
		KeyInfo::KeyRotateS,
		KeyInfo::KeyZoomIn,
		KeyInfo::KeyZoomOut,
	};

	constexpr static ButtonInfo buttonInfo[] =
	{
		ButtonInfo::ButtonUp,
		ButtonInfo::ButtonDown,
		ButtonInfo::ButtonRight,
		ButtonInfo::ButtonLeft,
		ButtonInfo::ButtonDecision,
		ButtonInfo::ButtonReturn,
	};

	// �L�[�̏��
	// �R���g���[���[�̏�Ԃ���������g�p
	enum KeyState
	{
		None,		// ������Ă��Ȃ�
		PushJust,	// �������u��
		Push,		// ������
		PushExit,	// ������
	};

	// �L�[�̏��
	struct KeyStateInfo
	{
		KeyState state = KeyState::None;
		KeyState prevState = KeyState::None;
	};

	// �L�[�{�[�h
	std::map<KeyInfo, KeyStateInfo> key;
	// �R���g���[���[
	std::map<ButtonInfo, KeyStateInfo> button;
	std::map<BYTE, KeyStateInfo> trigger;
	XINPUT_STATE xState;

	// �L�[�{�[�h
	void CheckKeyPushState(KeyInfo keycord);	// �L�[���������ۂ̏�ԑJ��
	void CheckKeyExitState(KeyInfo keycord);	// �L�[�𗣂����ۂ̏�ԑJ��
	// �R���g���[���[
	void CheckButtonPushState(ButtonInfo inButton);		// �{�^�����������ۂ̏�ԑJ��
	void CheckButtonExitState(ButtonInfo inButton);		// �{�^���𗣂����ۂ̏�ԑJ��

};
