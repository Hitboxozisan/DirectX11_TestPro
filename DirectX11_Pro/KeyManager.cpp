#pragma comment(lib, "xinput.lib")

#include <windows.h>
#include <math.h>
#include <xinput.h>
#include "KeyManager.h"
#include "EnumItr.h"

void KeyManager::KeyStateUpdate()
{
    BYTE keyboard[256];
    int a;
    
    for(auto& i : keyInfo)
    {
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

void KeyManager::CheckKeyExitState(KeyInfo keycord)
{
    if (key[keycord].prevState == KeyState::Push)
    {
        key[keycord].prevState == KeyState::PushExit;
    }
    if (key[keycord].prevState == KeyState::PushExit)
    {
        key[keycord].prevState == KeyState::None;
    }
}

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

bool KeyManager::IsKeyPush(KeyInfo keyInfo)
{
    return key[keyInfo].state == KeyState::Push;
}

bool KeyManager::IsKeyJust(KeyInfo keyInfo)
{
    return key[keyInfo].state == KeyState::PushJust;
}

bool KeyManager::IsKeyExit(KeyInfo keyInfo)
{
    return key[keyInfo].state == KeyState::PushJust;
}


