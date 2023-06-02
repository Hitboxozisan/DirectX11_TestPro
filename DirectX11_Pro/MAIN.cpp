
#include "MAIN.h"
#include "SceneManager.h"
#include "Application.h"
#include "D11Device.h"
#include "DirectXManager.h"

using namespace DirectX;

//グローバル変数
MAIN* g_pMain = NULL;
//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//
//アプリケーションのエントリー関数 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	g_pMain = new MAIN();
	if (g_pMain != NULL)
	{
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME)))
		{
			if (SUCCEEDED(g_pMain->Init()))
			{
				g_pMain->Loop();
			}
		}
		//アプリ終了
		g_pMain->DestroyD3D();
		delete g_pMain;
	}
	return 0;
}
//
//
//OSから見たウィンドウプロシージャー（実際の処理はMAINクラスのプロシージャーで処理）
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);
}

/// <summary>
/// コンストラクタ
/// </summary>
MAIN::MAIN()
	:device(Singleton<D11Device>::GetInstance())
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
MAIN::~MAIN()
{
	// 処理なし
}
//
//
//ウィンドウ作成
HRESULT MAIN::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
{
	// ウィンドウの定義
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);
	if (!hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return S_OK;
}
//
//
//ウィンドウプロシージャー
LRESULT MAIN::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE://ESCキーで修了
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

/// <summary>
/// 初期化処理
/// </summary>
HRESULT MAIN::Init()
{
	device.Init(hWnd);
	app = new Application();

	return S_OK;
}
//
//
//メッセージループとアプリケーション処理の入り口
void MAIN::Loop()
{
	app->Run();
}
//
//
//


//
//
//
void MAIN::DestroyD3D()
{
	//SAFE_RELEASE(swapChain);
	//SAFE_RELEASE(rtv);
	//SAFE_RELEASE(dsv);
	//SAFE_RELEASE(ds);
	//SAFE_RELEASE(device);
}
