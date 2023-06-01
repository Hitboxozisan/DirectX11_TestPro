#pragma comment(lib, "xinput.lib")

#include <windows.h>
#include <math.h>
#include <xinput.h>
#include "KeyManager.h"
#include "EnumItr.h"

/// <summary>
/// キーの状態を得る
/// </summary>
void KeyManager::KeyStateUpdate()
{
    BYTE keyboard[256];
    int a;
    
    for(auto& i : keyInfo)
    {
        key[i].prevState = key[i].state;
        if (GetKeyboardState(keyboard))
        {
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

void KeyManager::ButtonStateUpdate()
{
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

//KeyManager::~KeyManager()
//{
//    // 処理なし
//}


