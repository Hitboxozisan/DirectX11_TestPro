#pragma once
#include "Common.h"
#include "Framework.h"

class Application
{
public:
	// 初期化
	Application(HINSTANCE);

	// 解放
	~Application();


	LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	// 実行
	void Run();

private:

	class D11Device& device;
	class KeyManager& key;
	class SceneManager* sceneManager;

};

