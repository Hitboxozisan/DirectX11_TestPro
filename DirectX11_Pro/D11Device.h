#pragma once

#include <memory>
#include "DirectXManager.h"

class D11Device
{
public:
	D11Device();
	~D11Device();

	//LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	// ウィンドウの生成
	//HRESULT CreateGameWindow(HINSTANCE);
	bool Init(HWND hwnd);
	HRESULT InitD3D(HWND hwnd);
	// デバイス
	std::shared_ptr<DirectXManager> dx11;

	// ウィンドウハンドル
	//HWND hwnd;

private:


};

