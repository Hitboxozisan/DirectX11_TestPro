#include "SceneGame.h"
#include "D11Device.h"
#include "Camera.h"
#include "Text.h"
#include "TestObj.h"
#include "Singleton.h"
#include "Light.h"
#include "Player.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
SceneGame::SceneGame(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,device(Singleton<D11Device>::GetInstance())
	,camera(Singleton<Camera>::GetInstance())
	,text(Singleton<Text>::GetInstance())
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
	light = new Light();
	testObj = new TestObj();
	player = new Player();

	//light->SetLight({ 0.0f, 0.0f, 5.0f, -1.0f });
	//light->SetLight(XMVector3Normalize(light->GetLight()));
	//text.Init(WINDOW_WIDTH, WINDOW_HEIGHT, 23, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	camera.Init();
	testObj->Init();
	player->Init();
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
	camera.Update();
	camera.FollowUpPlayer(player->GetPos());
	player->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void SceneGame::Draw()
{
	XMMATRIX mView;
	XMMATRIX mProj;

	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0, 0, 0.5, 1 };// クリア色作成　RGBAの順
	device.dx11->GetDeviceContext()->ClearRenderTargetView(device.dx11->GetRtv(), ClearColor);					//画面クリア
	device.dx11->GetDeviceContext()->ClearDepthStencilView(device.dx11->GetDsv(), D3D11_CLEAR_DEPTH, 1.0f, 0);	//深度バッファクリア

	//text.Render("ABC", 50, 50);

	camera.Render();
	testObj->Render();
	player->Draw();


	//画面更新（バックバッファをフロントバッファに）
	device.dx11->GetSwapChain()->Present(1, 0);
}
