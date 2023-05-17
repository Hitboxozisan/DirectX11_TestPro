#pragma once

#include <map>

// �L�[���
enum KeyInfo
{
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	RotateR = 'E',
	RotateL = 'Q',
	ZoomIn  = 'P',
	ZoomOut = 'L',
	
};

/// <summary>
/// �L�[�̓��͔���
/// </summary>
class KeyManager
{
public:
	static KeyManager& GetInstance()
	{
		static KeyManager keyManager;
		return keyManager;
	};

	void KeyStateUpdate();						// �L�[����X�V����

	const bool IsKeyPush(KeyInfo keycord);
	bool IsKeyJust(KeyInfo keycord);
	bool IsKeyExit(KeyInfo keycord);
	
private:
	// �O������A�N�Z�X�𐧌�����
	//KeyManager();
	//KeyManager(const KeyManager&);
	//~KeyManager();
	
	// �L�[���z��
	constexpr static KeyInfo keyInfo[] =
	{
		KeyInfo::Up,
		KeyInfo::Down,
		KeyInfo::Left,
		KeyInfo::Right,
		KeyInfo::RotateR,
		KeyInfo::RotateL,
		KeyInfo::ZoomIn,
		KeyInfo::ZoomOut,
	};

	// �L�[�̏��
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

	std::map<KeyInfo, KeyStateInfo> key;

	void CheckKeyPushState(KeyInfo keycord);	// �L�[���������ۂ̏�ԑJ��
	void CheckKeyExitState(KeyInfo keycord);	// �L�[�𗣂����ۂ̏�ԑJ��

};
