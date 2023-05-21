#pragma once
class Application
{
public:
	// ‰Šú‰»
	Application();

	// ‰ğ•ú
	~Application();

	// Às
	void Run();

private:

	class D11Device& device;
	class KeyManager& key;
	class SceneManager* sceneManager;

};

