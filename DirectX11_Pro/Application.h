#pragma once
#include "Common.h"
#include "Framework.h"

class Application
{
public:
	// 初期化
	Application();

	// 解放
	~Application();

	// 実行
	void Run();

private:

	//class D11Device& device;
	class KeyManager& key;
	class SceneManager* sceneManager = nullptr;

};

