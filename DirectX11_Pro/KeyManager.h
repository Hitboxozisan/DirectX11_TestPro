#pragma once

/// <summary>
/// キーの入力判定
/// </summary>
class KeyManager
{
	// キー情報
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
		None,		// 押されていない
		PushJust,
		Push,
		Release,
	};

	void Input();

	bool GetKeyJust(KeyInfo keyInfo);
	bool GetKey(KeyInfo keyInfo);
	
	// キーの入力状態を保存する配列
	KeyState keyState[KeyInfo::keyAmount];
};

