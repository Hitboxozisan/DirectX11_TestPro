#include "D11Device.h"

D11Device::D11Device()
{
}

D11Device::~D11Device()
{
}

/// <summary>
/// ウィンドウプロシージャー
/// </summary>
/// <param name="hWnd"></param>
/// <param name="iMsg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT D11Device::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//return MsgProc(hWnd, uMsg, wParam, lParam);
}

bool D11Device::Init()
{

    // DirectX11ラッパー生成＆初期化
    dx11.reset(new DirectXManager(hwnd));
	

    return true;
}

void D11Device::CreateGameWindow(HINSTANCE hInstance, LPCWSTR windowName)
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
	wc.lpszClassName = windowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	hwnd = CreateWindow(windowName, windowName, WS_OVERLAPPEDWINDOW,
		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hInstance, 0);
	if (!hwnd)
	{
		return;
	}
	//ウインドウの表示
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//return S_OK;
}
