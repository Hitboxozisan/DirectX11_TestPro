#include "SceneGame.h"
#include "D11Device.h"
#include "Camera.h"
#include "TestObj.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
SceneGame::SceneGame(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
{
}

/// <summary>
/// デストラクタ
/// </summary>
SceneGame::~SceneGame()
{
}

/// <summary>
/// 初期化処理
/// </summary>
void SceneGame::Initialize()
{
	//device = inDevice;

	camera = new Camera();
	testObj = new TestObj();

	camera->Init();
	testObj->Init();
}

/// <summary>
/// 終了処理
/// </summary>
void SceneGame::Finalize()
{
}

/// <summary>
/// 活性化処理
/// </summary>
void SceneGame::Activate()
{
}

/// <summary>
/// 非活性化処理
/// </summary>
void SceneGame::Deactivate()
{
}

/// <summary>
/// 更新処理
/// </summary>
void SceneGame::Update()
{
	swapChain = device.dx11->GetSwapChain();

	camera->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void SceneGame::Draw()
{
	camera->Render();
	testObj->Render(camera->GetView(), camera->GetProj());

	//画面更新（バックバッファをフロントバッファに）
	swapChain->Present(1, 0);//テキストの後(執筆
}
