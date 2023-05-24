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
	deviceContext = device.dx11->GetDeviceContext().Get();
	swapChain = device.dx11->GetSwapChain();

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
	deviceContext->ClearRenderTargetView(device.dx11->GetRtv().Get(), ClearColor);					//画面クリア
	deviceContext->ClearDepthStencilView(device.dx11->GetDsv().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);	//深度バッファクリア

	camera->Render();
	testObj->Render(camera->GetView(), camera->GetProj());

	//画面更新（バックバッファをフロントバッファに）
	swapChain->Present(1, 0);//テキストの後(執筆
}
