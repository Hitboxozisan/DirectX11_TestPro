
#include "Application.h"
#include "Singleton.h"
#include "D11Device.h"
#include "KeyManager.h"
#include "SceneManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Application::Application()
	:key(Singleton<KeyManager>::GetInstance())
{
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
