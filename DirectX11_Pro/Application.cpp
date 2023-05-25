
#include "Application.h"
#include "Singleton.h"
#include "D11Device.h"
#include "KeyManager.h"
#include "SceneManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
Application::Application()
	:key(Singleton<KeyManager>::GetInstance())
{
	// シーンマネージャー
	sceneManager = new SceneManager();
	sceneManager->Initialize();
}

/// <summary>
/// デストラクタ
/// </summary>
Application::~Application()
{
}

/// <summary>
/// 更新処理
/// </summary>
void Application::Run()
{
	// メッセージループ
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
			// 操作関係更新処理
			key.KeyStateUpdate();
			// 各シーン更新処理
			sceneManager->Update();
			// 各シーン更新処理
			sceneManager->Draw();
		}
	}

	// アプリケーションの終了
}
