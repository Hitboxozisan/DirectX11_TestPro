#pragma once

#include <map>

/// <summary>
/// キーの入力判定
/// </summary>
class KeyManager
{
public:

	// キー情報
	enum KeyInfo : int
	{
		Up = VK_UP,
		Down = VK_DOWN,
		Left = VK_LEFT,
		Right = VK_RIGHT,
	};

	// キー情報配列
	constexpr static KeyInfo keyInfo[] =
	{
		KeyInfo::Up,
		KeyInfo::Down,
		KeyInfo::Left,
		KeyInfo::Right,
	};

	// キーの状態
	enum KeyState
	{
		None,		// 押されていない
		PushJust,	// 押した瞬間
		Push,		// 押した
		PushExit,	// 離した
	};

	// キーの状態
	struct KeyStateInfo
	{
		KeyState state = KeyState::None;
		KeyState prevState = KeyState::None;
	};

	void KeyStateUpdate();						// キー操作更新処理
	void CheckKeyPushState(KeyInfo keycord);	// キーを押した際の状態遷移
	void CheckKeyExitState(KeyInfo keycord);	// キーを離した際の状態遷移

	bool IsKeyPush(KeyInfo keyInfo);
	bool IsKeyJust(KeyInfo keyInfo);
	bool IsKeyExit(KeyInfo keyInfo);
	
private:
	std::map<KeyInfo, KeyStateInfo> key;
};
