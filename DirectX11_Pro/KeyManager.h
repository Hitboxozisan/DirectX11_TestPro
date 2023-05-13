#pragma once

#include <map>

// �L�[���
enum KeyInfo : int
{
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
};

/// <summary>
/// �L�[�̓��͔���
/// </summary>
class KeyManager
{
public:
	void KeyStateUpdate();						// �L�[����X�V����

	bool IsKeyPush(KeyInfo keyInfo);
	bool IsKeyJust(KeyInfo keyInfo);
	bool IsKeyExit(KeyInfo keyInfo);
	
private:
	// �L�[���z��
	constexpr static KeyInfo keyInfo[] =
	{
		KeyInfo::Up,
		KeyInfo::Down,
		KeyInfo::Left,
		KeyInfo::Right,
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
