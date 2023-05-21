#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneTitle.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneManager::SceneManager()
{
	eachScenes[TITLE] = new SceneTitle(this);
	eachScenes[GAME_MAIN] = new SceneGame(this);
	//eachScenes[RESULT] = new Result(this);

	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Initialize();
	}
	
	// �{����TITLE
	currentScene = nextScene = GAME_MAIN;
	currentPointer = eachScenes[currentScene];
	currentPointer->Activate();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
}

/// <summary>
/// �I������
/// </summary>
void SceneManager::Finalize()
{
	for (int i = 0; i < SceneManager::END; ++i)
	{
		eachScenes[i]->Finalize();
		delete eachScenes[i];
		eachScenes[i] = nullptr;
	}
}

/// <summary>
/// �X�V����
/// </summary>
void SceneManager::Update()
{
	if (currentScene != nextScene)
	{
		ChangeScene();		//���̃V�[��
	}

	if (currentPointer != nullptr)
	{
		currentPointer->Update();	//���݂̃V�[���̍X�V����
	}
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneManager::Draw()
{
	if (currentPointer != nullptr)
	{
		currentPointer->Draw();		//���݂̃V�[���̕`�揈��
	}
}

/// <summary>
/// ���̃V�[���ɑJ�ڂ���
/// </summary>
/// <param name="next"></param>
void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

/// <summary>
/// �V�[���̐؂�ւ�����
/// </summary>
void SceneManager::ChangeScene()
{
	if (nextScene == END)
	{
		return;
	}

	currentPointer->Deactivate();
	currentPointer = eachScenes[nextScene];
	currentScene = nextScene;
	currentPointer->Activate();
}

