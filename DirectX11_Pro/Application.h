#pragma once
class Application
{
public:
	// ������
	Application();

	// ���
	~Application();

	// ���s
	void Run();

private:

	class D11Device& device;
	class KeyManager& key;
	class SceneManager* sceneManager;

};

