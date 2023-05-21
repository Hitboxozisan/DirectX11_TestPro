#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneTitle.h"

/// <summary>
/// コンストラクタ
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
	
	// 本来はTITLE
	currentScene = nextScene = GAME_MAIN;
	currentPointer = eachScenes[currentScene];
	currentPointer->Activate();
}

/// <summary>
/// デストラクタ
/// </summary>
SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
}

/// <summary>
/// 終了処理
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
/// 更新処理
/// </summary>
void SceneManager::Update()
{
	if (currentScene != nextScene)
	{
		ChangeScene();		//次のシーン
	}

	if (currentPointer != nullptr)
	{
		currentPointer->Update();	//現在のシーンの更新処理
	}
}

/// <summary>
/// 描画処理
/// </summary>
void SceneManager::Draw()
{
	if (currentPointer != nullptr)
	{
		currentPointer->Draw();		//現在のシーンの描画処理
	}
}

/// <summary>
/// 次のシーンに遷移する
/// </summary>
/// <param name="next"></param>
void SceneManager::SetNextScene(Scene next)
{
	nextScene = next;
}

/// <summary>
/// シーンの切り替え処理
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

