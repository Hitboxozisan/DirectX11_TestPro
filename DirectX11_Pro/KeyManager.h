#pragma once

#include <map>
#include <Xinput.h>

namespace KeyMgrInfo
{

	// キー情報
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

	// コントローラーボタン情報
	enum ButtonInfo
	{
		ButtonUp = XINPUT_GAMEPAD_DPAD_UP,				// 矢印キー上
		ButtonDown = XINPUT_GAMEPAD_DPAD_DOWN,			// 矢印キー下
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT,		// 矢印キー右
		ButtonLeft = XINPUT_GAMEPAD_DPAD_LEFT,			// 矢印キー左
		ButtonDecision = XINPUT_GAMEPAD_A,				// 決定
		ButtonReturn = XINPUT_GAMEPAD_B,				// 戻る
	};
}

using namespace KeyMgrInfo;

/// <summary>
/// キーの入力判定
/// </summary>
class KeyManager
{
public:
	void InitController();
	void KeyStateUpdate();						// キー操作更新処理
	void ButtonStateUpdate();					// ボタン操作更新処理
	void StickStateUpdate();

	// キーボード
	const bool IsKeyPush(KeyInfo keycord);
	bool IsKeyJust(KeyInfo keycord);
	bool IsKeyExit(KeyInfo keycord);
	// コントローラー
	 // ボタン
	const bool IsButtonPush(ButtonInfo inButton);
	bool IsButtonJust(ButtonInfo inButton);
	bool IsButtonExit(ButtonInfo inButton);
	 // 右トリガー
	bool IsCheckRTrigger();
	 // 左トリガー
	bool IsCheckLTrigger();
	
	
private:
	// 外部からアクセスを制限する
	//KeyManager();
	//KeyManager(const KeyManager&);
	//~KeyManager();
	
	// キー情報配列
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

	// キーの状態
	// コントローラーの状態もこちらを使用
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

	// キーボード
	std::map<KeyInfo, KeyStateInfo> key;
	// コントローラー
	std::map<ButtonInfo, KeyStateInfo> button;
	std::map<BYTE, KeyStateInfo> trigger;
	XINPUT_STATE xState;

	// キーボード
	void CheckKeyPushState(KeyInfo keycord);	// キーを押した際の状態遷移
	void CheckKeyExitState(KeyInfo keycord);	// キーを離した際の状態遷移
	// コントローラー
	void CheckButtonPushState(ButtonInfo inButton);		// ボタンを押した際の状態遷移
	void CheckButtonExitState(ButtonInfo inButton);		// ボタンを離した際の状態遷移

};
