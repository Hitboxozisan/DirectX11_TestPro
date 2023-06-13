#pragma comment(lib, "xinput.lib")

#include <windows.h>
#include <math.h>
#include <xinput.h>
#include "KeyManager.h"
#include "EnumItr.h"

// ������擾�̂���
using namespace KeyMgrInfo;

/// <summary>
/// �L�[�̏�Ԃ𓾂�
/// </summary>
void KeyManager::KeyStateUpdate()
{
    BYTE keyboard[256];
    int a;
    
    for(auto& i : keyInfo)
    {
        // �L�[�̓��͏�Ԃ��X�V
        key[i].prevState = key[i].state;
        if (GetKeyboardState(keyboard))
        {
            // �����ꂽ�ꍇ
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
/// �R���g���[���[�{�^���X�V����
/// </summary>
void KeyManager::ButtonStateUpdate()
{
    ZeroMemory(&xState, sizeof(XINPUT_STATE));
   

    for (auto& i : buttonInfo)
    {
        DWORD result = XInputGetState(0, &xState);

        // �{�^���̓��͏�Ԃ��X�V
        button[i].prevState = button[i].state;
        // �ڑ����Ă���
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
        // �ڑ����Ă��Ȃ�
        else
        {
            // �ڑ�����Ă��Ȃ����Ƃ���ʏ�ɕ\��
        }
    }
}

/// <summary>
/// �A�i���O�X�e�B�b�N�X�V����
/// </summary>
void KeyManager::StickStateUpdate()
{
    // �f�b�h�]�[���ȉ��̏ꍇ�͐��l��0�ɂ���
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
/// �R���g���[���[�Ăяo��
/// </summary>
void KeyManager::InitController()
{
    // XInput�̏�����
    //XInputEnable(true);

}

void KeyManager::Update()
{
    KeyStateUpdate();
    ButtonStateUpdate();
    StickStateUpdate();
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
/// �{�^�����������ۂ̏�ԑJ��
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
/// �{�^���𗣂����ۂ̏�ԑJ��
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

/// <summary>
/// �{�^������������
/// </summary>
/// <param name="inButton"></param>
/// <returns></returns>
const bool KeyManager::IsButtonPush(ButtonInfo inButton)
{
    return button[inButton].state == KeyState::Push;
}

/// <summary>
/// �{�^�����������u�Ԃ�
/// </summary>
/// <param name="inButton"></param>
/// <returns></returns>
bool KeyManager::IsButtonJust(ButtonInfo inButton)
{
    return xState.Gamepad.wButtons == KeyState::PushJust;
}

/// <summary>
/// �{�^���𗣂�����
/// </summary>
/// <param name="inButton"></param>
/// <returns></returns>
bool KeyManager::IsButtonExit(ButtonInfo inButton)
{
    return xState.Gamepad.wButtons == KeyState::PushExit;
}

/// <summary>
/// �E�g���K�[�̉������
/// </summary>
/// <returns>true : ������</returns>
bool KeyManager::IsCheckRTrigger()
{
    return xState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
}

/// <summary>
/// ���g���K�[�̉������
/// </summary>
/// <returns>true : ������</returns>
bool KeyManager::IsCheckLTrigger()
{
    return xState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD;
}

/// <summary>
/// �E�X�e�B�b�N�̓��͏�Ԃ�Ԃ�(x, y)
/// ���K���ς�
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
/// ���X�e�B�b�N�̓��͏�Ԃ�Ԃ�(x, y)
/// ���K���ς�
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




