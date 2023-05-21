#pragma once
#include "Framework.h"
#include "SceneBase.h"

/// <summary>
/// �V�[���J�ځE�Ǘ��N���X
/// </summary>
class SceneManager
{
public:
	// �V�[����Ԓ�`
	enum Scene
	{
		TITLE = 0,	// �^�C�g�����
		GAME_MAIN,	// �Q�[�����
		//RESULT,	// ���U���g���
		END			// �I������@���@�V�[���̌�
	};

	SceneManager();
	~SceneManager();

	void Initialize();
	void Finalize();
	void Update();
	void Draw();

	void SetNextScene(Scene next);
	Scene GetCurrentScene() { return currentScene; }
	Scene GetNextScene() { return nextScene; }
private:
	SceneManager(const SceneManager&);		// �R�s�[�R���X�g���N�^
	void operator=(const SceneManager&);	// �R�s�[������Z�q

	SceneBase* eachScenes[Scene::END];		// �e�V�[���̃C���X�^���X
	SceneBase* currentPointer;				// ���݂̃V�[���̃|�C���^
	Scene	   currentScene;				// ���݂̃V�[��
	Scene	   nextScene;					// ���̃V�[��

	void ChangeScene();

	//HWND hWnd;
	//ID3D11Device* device;
	//ID3D11DeviceContext* deviceContext;
	//IDXGISwapChain* swapChain;
	//ID3D11RenderTargetView* rtv;
	//ID3D11DepthStencilView* dsv;
	//ID3D11DepthStencilState* depthStencilState;
	//ID3D11Texture2D* ds;
};

