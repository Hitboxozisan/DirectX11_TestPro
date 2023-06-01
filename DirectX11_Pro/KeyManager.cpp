#pragma comment(lib, "xinput.lib")

#include <windows.h>
#include <math.h>
#include <xinput.h>
#include "KeyManager.h"
#include "EnumItr.h"

/// <summary>
/// �L�[�̏�Ԃ𓾂�
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
/// �L�[�𗣂����ۂ̏�ԑJ��
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
/// �L�[���������ۂ̏�ԑJ��
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
/// �L�[�������Ă邩
/// </summary>
/// <param name="keyInfo"></param>
/// <returns></returns>
const bool KeyManager::IsKeyPush(KeyInfo keycord)
{
    return key[keycord].state == KeyState::Push;
}

/// <summary>
/// �L�[���������u�Ԃ�
/// </summary>
/// <param name="keyInfo"></param>
/// <returns></returns>
bool KeyManager::IsKeyJust(KeyInfo keycord)
{
    return key[keycord].state == KeyState::PushJust;
}

/// <summary>
/// �L�[�𗣂�����
/// </summary>
/// <param name="keyInfo"></param>
/// <returns></returns>
bool KeyManager::IsKeyExit(KeyInfo keycord)
{
    return key[keycord].state == KeyState::PushJust;
}

//KeyManager::~KeyManager()
//{
//    // �����Ȃ�
//}


