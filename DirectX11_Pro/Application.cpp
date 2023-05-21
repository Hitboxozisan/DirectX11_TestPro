#include "Application.h"
#include "Singleton.h"
#include "D11Device.h"
#include "KeyManager.h"
#include "SceneManager.h"

Application::Application()
	:device(Singleton<D11Device>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
{
	if (device.Init())
	{
		return;
	}
	ShowWindow(device.hwnd, SW_SHOW);

	// �V�[���}�l�[�W���[
	sceneManager = new SceneManager();
	sceneManager->Initialize();
}

Application::~Application()
{
}

void Application::Run()
{

	// ����֌W�X�V����
	key.KeyStateUpdate();

}
