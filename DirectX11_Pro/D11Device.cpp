#include "D11Device.h"

// 関数プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

D11Device::D11Device()
{
	
}

D11Device::~D11Device()
{
}

/// <summary>
/// ウィンドウプロシージャー
/// </summary>
//LRESULT D11Device::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMsg)
//	{
//	case WM_KEYDOWN:
//		switch ((char)wParam)
//		{
//		case VK_ESCAPE://ESCキーで修了
//			PostQuitMessage(0);
//			break;
//		}
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	}
//	return DefWindowProc(hWnd, iMsg, wParam, lParam);
//}

bool D11Device::Init(HWND hwnd)
{
	// DirectX11ラッパー生成＆初期化
    dx11.reset(new DirectXManager(hwnd));

	//if (SUCCEEDED(CreateGameWindow(hInstance)))
	//{
	//	InitD3D();
	//}

    return true;
}

HRESULT D11Device::InitD3D(HWND hwnd)
{
	dx11->CreateSwapChain(hwnd);
	dx11->CreateRencerTargetAndDepthStencil();
	dx11->CreateDepthStencilView();
	dx11->SettingViewport();
	dx11->SettingRasterizer();

	return S_OK;
}

//HRESULT D11Device::CreateGameWindow(HINSTANCE hInstance)
//{
//	// ウィンドウの定義
//	WNDCLASSEX  wc;
//	ZeroMemory(&wc, sizeof(wc));
//	wc.cbSize = sizeof(wc);
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WndProc;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
//	wc.lpszClassName = APP_NAME;
//	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//	RegisterClassEx(&wc);
//
//	//ウィンドウの作成
//	hwnd = CreateWindow(APP_NAME, APP_NAME, WS_OVERLAPPEDWINDOW,
//		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hInstance, 0);
//	if (!hwnd)
//	{
//		return E_FAIL;
//	}
//	//ウインドウの表示
//	ShowWindow(hwnd, SW_SHOW);
//	UpdateWindow(hwnd);
//
//	return S_OK;
//}
