#pragma once

#include <map>

/// <summary>
/// �L�[�̓��͔���
/// </summary>
class KeyManager
{
public:

	// �L�[���
	enum KeyInfo : int
	{
		Up = VK_UP,
		Down = VK_DOWN,
		Left = VK_LEFT,
		Right = VK_RIGHT,
	};

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

	void KeyStateUpdate();						// �L�[����X�V����
	void CheckKeyPushState(KeyInfo keycord);	// �L�[���������ۂ̏�ԑJ��
	void CheckKeyExitState(KeyInfo keycord);	// �L�[�𗣂����ۂ̏�ԑJ��

	bool IsKeyPush(KeyInfo keyInfo);
	bool IsKeyJust(KeyInfo keyInfo);
	bool IsKeyExit(KeyInfo keyInfo);
	
private:
	std::map<KeyInfo, KeyStateInfo> key;
};
