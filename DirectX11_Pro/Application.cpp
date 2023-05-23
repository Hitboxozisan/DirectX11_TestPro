

#include "Application.h"
#include "Singleton.h"
#include "D11Device.h"
#include "KeyManager.h"
#include "SceneManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Application::Application(HINSTANCE hInstance)
	:device(Singleton<D11Device>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
{
	// DirectX�֌W����������
 	if (device.Init(hInstance))
	{
		return;
	}

	// �V�[���}�l�[�W���[
	sceneManager = new SceneManager();
	sceneManager->Initialize();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Application::~Application()
{
}

LRESULT Application::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return device.MsgProc(hWnd, uMsg, wParam, lParam);
}

/// <summary>
/// �X�V����
/// </summary>
void Application::Run()
{
	// ���b�Z�[�W���[�v
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// ����֌W�X�V����
			key.KeyStateUpdate();
			// �e�V�[���X�V����
			sceneManager->Update();
			// �e�V�[���X�V����
			sceneManager->Draw();
		}
	}

	// �A�v���P�[�V�����̏I��
}
