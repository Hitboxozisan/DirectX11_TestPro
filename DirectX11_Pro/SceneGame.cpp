#include "SceneGame.h"
#include "D11Device.h"
#include "Camera.h"
#include "TestObj.h"
#include "Singleton.h"
#include "Light.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="sceneManager"></param>
SceneGame::SceneGame(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,device(Singleton<D11Device>::GetInstance())
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
	camera = new Camera();
	testObj = new TestObj();

	//light->SetLight({ 0.0f, 0.0f, 5.0f, -1.0f });
	//light->SetLight(XMVector3Normalize(light->GetLight()));
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
	camera->Update();
}

/// <summary>
/// 描画処理
/// </summary>
void SceneGame::Draw()
{
	XMMATRIX mView;
	XMMATRIX mProj;
	//画面クリア（実際は単色で画面を塗りつぶす処理）
	float ClearColor[4] = { 0,0,1,1 };// クリア色作成　RGBAの順
	device.dx11->GetDeviceContext()->ClearRenderTargetView(device.dx11->GetRtv().Get(), ClearColor);					//画面クリア
	device.dx11->GetDeviceContext()->ClearDepthStencilView(device.dx11->GetDsv().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);	//深度バッファクリア

	//camera->Render();
	//testObj->Render(camera->GetView(), camera->GetProj());

	//画面更新（バックバッファをフロントバッファに）
	device.dx11->GetSwapChain()->Present(1, 0);
}
