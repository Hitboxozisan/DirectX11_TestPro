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

	// �f�o�C�X
	std::shared_ptr<DirectXManager> dx11;

	// �E�B���h�E�n���h��
	HWND hwnd;

private:

	// �E�B���h�E�̐���
	void CreateGameWindow(HINSTANCE, LPCWSTR windowName);

};

