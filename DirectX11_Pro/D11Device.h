#pragma once

#include <memory>
#include "DirectXManager.h"

class D11Device
{
public:
	D11Device();
	~D11Device();

	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	bool Init(HINSTANCE);
	HRESULT InitD3D();

	// デバイス
	std::shared_ptr<DirectXManager> dx11;

	// ウィンドウハンドル
	HWND hwnd;

private:

	// ウィンドウの生成
	HRESULT CreateGameWindow(HINSTANCE);

};

