#pragma comment(lib, "xinput.lib")

#include <windows.h>
#include <math.h>
#include <xinput.h>
#include "KeyManager.h"
#include "EnumItr.h"

// 操作情報取得のため
using namespace KeyMgrInfo;

/// <summary>
/// キーの状態を得る
/// </summary>
void KeyManager::KeyStateUpdate()
{
    BYTE keyboard[256];
    int a;
    
    for(auto& i : keyInfo)
    {
        // キーの入力状態を更新
        key[i].prevState = key[i].state;
        if (GetKeyboardState(keyboard))
        {
            // 押された場合
            if (keyboard[i] & 0x80)
            {
                CheckKeyPushState(i);
            }
            else
            {
                CheckKeyExitState(i);
            }
        }
    }

}

/// <summary>
/// コントローラーボタン更新処理
/// </summary>
void KeyManager::ButtonStateUpdate()
{
    ZeroMemory(&xState, sizeof(XINPUT_STATE));
   

    for (auto& i : buttonInfo)
    {
        DWORD result = XInputGetState(0, &xState);

        // ボタンの入力状態を更新
        button[i].prevState = button[i].state;
        // 接続している
        if (result == ERROR_SUCCESS)
        {
            if (xState.Gamepad.wButtons == (WORD)i)
            {
                CheckButtonPushState(i);
            }
            else
            {
                CheckButtonExitState(i);
            }
        }
        // 接続していない
        else
        {
            // 接続されていないことを画面上に表示
        }
    }
}

/// <summary>
/// アナログスティック更新処理
/// </summary>
void KeyManager::StickStateUpdate()
{
    // デッドゾーン以下の場合は数値を0にする
    if ((xState.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
        xState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
        (xState.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
            xState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
    {
        xState.Gamepad.sThumbLX = 0;
        xState.Gamepad.sThumbLY = 0;
    }
   
}


/// <summary>
/// コントローラー呼び出し
/// </summary>
void KeyManager::InitController()
{
    // XInputの初期化
    //XInputEnable(true);

}

void KeyManager::Update()
{
    KeyStateUpdate();
    ButtonStateUpdate();
    StickStateUpdate();
}

/// <summary>
/// キーを離した際の状態遷移
/// </summary>
/// <param name="keycord"></param>
void KeyManager::CheckKeyExitState(KeyInfo keycord)
{
    if (key[keycord].prevState == KeyState::Push)
    {
        key[keycord].state = KeyState::PushExit;
    }
    if (key[keycord].prevState == KeyState::PushExit)
    {
        key[keycord].state = KeyState::None;
    }
}

/// <summary>
/// ボタンを押した際の状態遷移
/// </summary>
/// <param name="button"></param>
void KeyManager::CheckButtonPushState(ButtonInfo inButton)
{
    if (button[inButton].prevState == KeyState::None)
    {
        button[inButton].state = KeyState::PushJust;
    }
    if (button[inButton].prevState == KeyState::PushJust)
    {
        button[inButton].state = KeyState::Push;
    }
}

/// <summary>
/// ボタンを離した際の状態遷移
/// </summary>
/// <param name="button"></param>
void KeyManager::CheckButtonExitState(ButtonInfo inButton)
{
    if (button[inButton].prevState == KeyState::Push)
    {
        button[inButton].state = KeyState::PushExit;
    }
    if (button[inButton].prevState == KeyState::PushExit)
    {
        button[inButton].state = KeyState::None;
    }
}

/// <summary>
/// キーを押した際の状態遷移
/// </summary>
/// <param name="keycord"></param>
void KeyManager::CheckKeyPushState(KeyInfo keycord)
{
    if (key[keycord].prevState == KeyState::None)
    {
        key[keycord].state = KeyState::PushJust;
    }
    if (key[keycord].prevState == KeyState::PushJust)
    {
        key[keycord].state = KeyState::Push;
    }
}

/// <summary>
/// キーを押してるか
/// </summary>
/// <param name="keyInfo"></param>
/// <returns></returns>
const bool KeyManager::IsKeyPush(KeyInfo keycord)
{
    return key[keycord].state == KeyState::Push;
}

/// <summary>
/// キーを押した瞬間か
/// </summary>
/// <param name="keyInfo"></param>
/// <returns></returns>
bool KeyManager::IsKeyJust(KeyInfo keycord)
{
    return key[keycord].state == KeyState::PushJust;
}

/// <summary>
/// キーを離したか
/// </summary>
/// <param name="keyInfo"></param>
/// <returns></returns>
bool KeyManager::IsKeyExit(KeyInfo keycord)
{
    return key[keycord].state == KeyState::PushJust;
}

/// <summary>
/// ボタンを押したか
/// </summary>
/// <param name="inButton"></param>
/// <returns></returns>
const bool KeyManager::IsButtonPush(ButtonInfo inButton)
{
    return button[inButton].state == KeyState::Push;
}

/// <summary>
/// ボタンを押した瞬間か
/// </summary>
/// <param name="inButton"></param>
/// <returns></returns>
bool KeyManager::IsButtonJust(ButtonInfo inButton)
{
    return xState.Gamepad.wButtons == KeyState::PushJust;
}

/// <summary>
/// ボタンを離したか
/// </summary>
/// <param name="inButton"></param>
/// <returns></returns>
bool KeyManager::IsButtonExit(ButtonInfo inButton)
{
    return xState.Gamepad.wButtons == KeyState::PushExit;
}

/// <summary>
/// 右トリガーの押下状態
/// </summary>
/// <returns>true : 押した</returns>
bool KeyManager::IsCheckRTrigger()
{
    return xState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
}

/// <summary>
/// 左トリガーの押下状態
/// </summary>
/// <returns>true : 押した</returns>
bool KeyManager::IsCheckLTrigger()
{
    return xState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
}

/// <summary>
/// 右スティックの入力状態を返す(x, y)
/// 正規化済み
/// </summary>
/// <returns></returns>
XMFLOAT2 KeyManager::GetRStickInput()
{
    XMVECTOR nor = XMVectorSet(xState.Gamepad.sThumbRX, xState.Gamepad.sThumbRY, 0.0f, 0.0f);
    nor = XMVector2Normalize(nor);

    XMFLOAT2 result;
    XMStoreFloat2(&result, nor);

    return result;
}

/// <summary>
/// 左スティックの入力状態を返す(x, y)
/// 正規化済み
/// </summary>
/// <returns></returns>
XMFLOAT2 KeyManager::GetLStickInput()
{
    XMVECTOR nor = XMVectorSet(xState.Gamepad.sThumbLX, xState.Gamepad.sThumbLY, 0.0f, 0.0f);
    nor = XMVector2Normalize(nor);

    XMFLOAT2 result;
    XMStoreFloat2(&result, nor);

    return result;
}




