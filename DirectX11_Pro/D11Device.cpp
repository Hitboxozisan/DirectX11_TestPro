#include "D11Device.h"

D11Device::D11Device()
	:dx11(nullptr)
{
}

D11Device::~D11Device()
{
}

/// <summary>
/// �E�B���h�E�v���V�[�W���[
/// </summary>
//LRESULT D11Device::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMsg)
//	{
//	case WM_KEYDOWN:
//		switch ((char)wParam)
//		{
//		case VK_ESCAPE://ESC�L�[�ŏC��
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

bool D11Device::Init(const HWND& hwnd)
{
	// DirectX11���b�p�[������������
    dx11.reset(new DirectXManager(hwnd));
	
	if (FAILED(InitD3D()))
	{
		return false;
	}

    return true;
}

HRESULT D11Device::InitD3D()
{
	if (FAILED(dx11->CreateSwapChain()))
	{
		return E_FAIL;
	}
	if (FAILED(dx11->CreateRencerTargetAndDepthStencil()))
	{
		return E_FAIL;
	}

	dx11->SettingViewport();
	dx11->SettingRasterizer();

	return S_OK;
}

//HRESULT D11Device::CreateGameWindow(HINSTANCE hInstance)
//{
//	// �E�B���h�E�̒�`
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
//	//�E�B���h�E�̍쐬
//	hwnd = CreateWindow(APP_NAME, APP_NAME, WS_OVERLAPPEDWINDOW,
//		0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0, hInstance, 0);
//	if (!hwnd)
//	{
//		return E_FAIL;
//	}
//	//�E�C���h�E�̕\��
//	ShowWindow(hwnd, SW_SHOW);
//	UpdateWindow(hwnd);
//
//	return S_OK;
//}
