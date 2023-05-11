#pragma comment(lib, "xinput.lib")

#include "KeyManager.h"
#include <xinput.h>
#include <math.h>
#include <winuser.h>

void KeyManager::Input()
{
    int iKeyA = 0, iKeyD = 0, iKeyW = 0, iKeyS = 0;
    // �L�[����
    if (GetAsyncKeyState('A') & 0x8000) iKeyA = 1;
    if (GetAsyncKeyState('D') & 0x8000) iKeyD = 1;
    if (GetAsyncKeyState('W') & 0x8000) iKeyW = 1;
    if (GetAsyncKeyState('S') & 0x8000) iKeyS = 1;
	
    //�L�[���͎��̏���
    double dValue = 1;
    if (iKeyA || iKeyD)
    {
        if (iKeyW || iKeyS)
        {
            dValue = 1 / sqrt(2);//�΂ߓ��͎���1/��2�{����
        }
        else
        {
            dValue = 1;
        }
    }
    else if (iKeyW || iKeyS)
    {
        dValue = 1;
    }

}

bool KeyManager::GetKeyJust(KeyInfo keyInfo)
{
    return ;
}

bool KeyManager::GetKey(KeyInfo keyInfo)
{
    return false;
}
