#pragma once

#include <map>

// キー情報
enum KeyInfo
{
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT,
	RotateR = 'E',
	RotateL = 'Q',
	RotateW = 'W',
	RotateS = 'S',
	ZoomIn  = 'P',
	ZoomOut = 'L',
	
};

enum ButtonInfo
{
	Forward,		// 前
	Back,			// 後ろ
	Right,			// 右
	Left,			// 左
	Decision,		// 決定
	Return,			// 戻る
};

/// <summary>
/// キーの入力判定
/// </summary>
class KeyManager
{
public:
	void KeyStateUpdate();						// キー操作更新処理
	void ButtonStateUpdate();					// ボタン操作更新処理

	const bool IsKeyPush(KeyInfo keycord);
	bool IsKeyJust(KeyInfo keycord);
	bool IsKeyExit(KeyInfo keycord);
	
private:
	// 外部からアクセスを制限する
	//KeyManager();
	//KeyManager(const KeyManager&);
	//~KeyManager();
	
	// キー情報配列
	constexpr static KeyInfo keyInfo[] =
	{
		KeyInfo::Up,
		KeyInfo::Down,
		KeyInfo::Left,
		KeyInfo::Right,
		KeyInfo::RotateR,
		KeyInfo::RotateL,
		KeyInfo::RotateW,
		KeyInfo::RotateS,
		KeyInfo::ZoomIn,
		KeyInfo::ZoomOut,
	};

	constexpr static ButtonInfo buttonInfo[] =
	{
		ButtonInfo::Forward,
		ButtonInfo::Back,
		ButtonInfo::Right,
		ButtonInfo::Left,
		ButtonInfo::Decision,
		ButtonInfo::Return,
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

	std::map<KeyInfo, KeyStateInfo> key;

	void CheckKeyPushState(KeyInfo keycord);	// キーを押した際の状態遷移
	void CheckKeyExitState(KeyInfo keycord);	// キーを離した際の状態遷移

};
