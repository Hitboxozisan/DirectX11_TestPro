#pragma once
#include "Common.h"
#include "Framework.h"

class Application
{
public:
	// ������
	Application();

	// ���
	~Application();


	//LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// ���s
	void Run();

private:

	//class D11Device& device;
	class KeyManager& key;
	class SceneManager* sceneManager = nullptr;

};

