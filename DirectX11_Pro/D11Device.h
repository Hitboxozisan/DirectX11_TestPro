#pragma once

#include <memory>
#include "DirectXManager.h"

class D11Device
{
public:
	D11Device();
	~D11Device();

	//LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	// �E�B���h�E�̐���
	//HRESULT CreateGameWindow(HINSTANCE);
	bool Init(HWND hwnd);
	HRESULT InitD3D(HWND hwnd);
	// �f�o�C�X
	std::shared_ptr<DirectXManager> dx11;

	// �E�B���h�E�n���h��
	//HWND hwnd;

private:


};

