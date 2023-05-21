#pragma once

#include <memory>
#include "DirectXManager.h"

class D11Device
{
public:
	D11Device();
	~D11Device();


	bool Init();
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	// デバイス
	std::shared_ptr<DirectXManager> dx11;

	// ウィンドウハンドル
	HWND hwnd;

private:

	// ウィンドウの生成
	void CreateGameWindow(HINSTANCE, LPCWSTR windowName);

};

