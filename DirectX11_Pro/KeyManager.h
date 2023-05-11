#pragma once

/// <summary>
/// �L�[�̓��͔���
/// </summary>
class KeyManager
{
	// �L�[���
	enum KeyInfo
	{
		ArrowUp,
		ArrowDown,
		ArrowLeft,
		ArrowRight,

		keyAmount,
	};

	enum KeyState
	{
		None,		// ������Ă��Ȃ�
		PushJust,
		Push,
		Release,
	};

	void Input();

	bool GetKeyJust(KeyInfo keyInfo);
	bool GetKey(KeyInfo keyInfo);
	
	// �L�[�̓��͏�Ԃ�ۑ�����z��
	KeyState keyState[KeyInfo::keyAmount];
};

