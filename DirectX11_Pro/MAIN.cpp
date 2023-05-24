
#include "MAIN.h"
#include "SceneManager.h"
#include "Text.h"
#include "Fps.h"
#include "TestPolygon.h"
#include "Light.h"
#include "PointSprite3D.h"
#include "TestObj.h"
#include "Singleton.h"
#include "KeyManager.h"
#include "Camera.h"
#include "SphereMap.h"
#include "Application.h"
#include "D11Device.h"
#include "DirectXManager.h"

using namespace DirectX;

//グローバル変数
MAIN* g_pMain = NULL;
//関数プロトタイプの宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//
//アプリケーションのエントリー関数 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	g_pMain = new MAIN();
	if (g_pMain != NULL)
	{
		if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME)))
		{
			if (SUCCEEDED(g_pMain->Init()))
			{
				g_pMain->Loop();
			}
		}
		//アプリ終了
		g_pMain->DestroyD3D();
		delete g_pMain;
	}
	return 0;
}
//
//
//OSから見たウィンドウプロシージャー（実際の処理はMAINクラスのプロシージャーで処理）
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return g_pMain->MsgProc(hWnd, uMsg, wParam, lParam);
}

/// <summary>
/// コンストラクタ
/// </summary>
MAIN::MAIN()
	:device(Singleton<D11Device>::GetInstance())
{
	
}

/// <summary>
/// デストラクタ
/// </summary>
MAIN::~MAIN()
{
	// 処理なし
}
//
//
//ウィンドウ作成
HRESULT MAIN::InitWindow(HINSTANCE hInstance,
	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
{
	// ウィンドウの定義
	WNDCLASSEX  wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = WindowName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);

	//ウィンドウの作成
	hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);
	if (!hWnd)
	{
		return E_FAIL;
	}
	//ウインドウの表示
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	return S_OK;
}
//
//
//ウィンドウプロシージャー
LRESULT MAIN::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_KEYDOWN:
		switch ((char)wParam)
		{
		case VK_ESCAPE://ESCキーで修了
			PostQuitMessage(0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, iMsg, wParam, lParam);
}

/// <summary>
/// 初期化処理
/// </summary>
HRESULT MAIN::Init()
{

	//light = new Light;
	//light->SetLight({ 0.0f, 0.0f, 5.0f, -1.0f });
	//light->SetLight(XMVector3Normalize(light->GetLight()));

	device.Init(hWnd);
	device.InitD3D(hWnd);

	app = new Application();

	//if (FAILED(InitD3D()))
	//{
	//	return E_FAIL;
	//}


	return S_OK;
}
//
//
//メッセージループとアプリケーション処理の入り口
void MAIN::Loop()
{
	app->Run();
}
//
//
//
HRESULT MAIN::InitD3D()
{

	//HRESULT result;
	//
	//// デバイスとスワップチェーンの作成
	//DXGI_SWAP_CHAIN_DESC sd;
	//ZeroMemory(&sd, sizeof(sd));
	//sd.BufferCount = 1;
	//sd.BufferDesc.Width = WINDOW_WIDTH;
	//sd.BufferDesc.Height = WINDOW_HEIGHT;
	//sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	//sd.BufferDesc.RefreshRate.Numerator = FLAME_RATE;
	//sd.BufferDesc.RefreshRate.Denominator = 1;
	//sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//sd.OutputWindow = hWnd;
	//sd.SampleDesc.Count = 1;
	//sd.SampleDesc.Quality = 0;
	//sd.Windowed = TRUE;
	//
	//D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	//D3D_FEATURE_LEVEL* pFeatureLevel = NULL;
	//
	//if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
	//	0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &device.dx11->GetSwapChain(), &device.dx11->GetDevice(),
	//	pFeatureLevel, &device.dx11->GetDeviceContext())))
	//{
	//	return FALSE;
	//}
	//
	//
	////レンダーターゲットビューの作成
	//ID3D11Texture2D* pBackBuffer = nullptr;
	//swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	//// そのテクスチャーに対しレンダーターゲットビューを作成
	//if (FAILED(device->CreateRenderTargetView(pBackBuffer, NULL, &rtv)))
	//{
	//	return E_FAIL;
	//}
	//SAFE_RELEASE(pBackBuffer);
	//
	////深度ステンシルビューの作成
	//D3D11_TEXTURE2D_DESC descDepth;
	//descDepth.Width = WINDOW_WIDTH;
	//descDepth.Height = WINDOW_HEIGHT;
	//descDepth.MipLevels = 1;
	//descDepth.ArraySize = 1;
	//descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	//descDepth.SampleDesc.Count = 1;
	//descDepth.SampleDesc.Quality = 0;
	//descDepth.Usage = D3D11_USAGE_DEFAULT;
	//descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//descDepth.CPUAccessFlags = 0;
	//descDepth.MiscFlags = 0;
	//result = device->CreateTexture2D(&descDepth, NULL, &ds);
	//if (FAILED(result))
	//{
	//	return E_FAIL;
	//}
	//// そのテクスチャーに対しデプスステンシルビューを作成
	//result = device->CreateDepthStencilView(ds, NULL, &dsv);
	//if (FAILED(result))
	//{
	//	return E_FAIL;
	//}
	//
	////レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	//deviceContext->OMSetRenderTargets(1, &rtv, dsv);
	

	// 深度テストを無効にする
	//D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	//ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
	//depthStencilDesc.DepthEnable = false;
	//
	//device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	//deviceContext->OMSetDepthStencilState(depthStencilState, 1);

	//ビューポートの設定
	//D3D11_VIEWPORT vp;
	//vp.Width = WINDOW_WIDTH;
	//vp.Height = WINDOW_HEIGHT;
	//vp.MinDepth = 0.0f;
	//vp.MaxDepth = 1.0f;
	//vp.TopLeftX = 0;
	//vp.TopLeftY = 0;
	//deviceContext->RSSetViewports(1, &vp);
	//ラスタライズ設定
	//D3D11_RASTERIZER_DESC rdc;
	//ZeroMemory(&rdc, sizeof(rdc));
	//rdc.CullMode = D3D11_CULL_NONE;
	//rdc.FillMode = D3D11_FILL_SOLID;
	//ID3D11RasterizerState* pIr = NULL;
	//device->CreateRasterizerState(&rdc, &pIr);
	//deviceContext->RSSetState(pIr);
	//SAFE_RELEASE(pIr);


	// Xinputを初期化
	//XInputEnable(true);

	// 各インスタンス生成

	//文字列レンダリングの初期化
	//text = new Text;
	//XMFLOAT4 vColor(1.0f, 0.0f, 0.0f, 1.0f);
	//if (FAILED(text->Init(deviceContext, WINDOW_WIDTH, WINDOW_HEIGHT, 25, vColor)))
	//{
	//	return E_FAIL;
	//}
	// フレームレート
	//fps = new Fps;
	//fps->Init(text);

	//testObj = new TestObj;
	//testObj->Init(device, deviceContext, swapChain);
	//
	//// カメラクラス
	//camera = new Camera();
	//camera->Init();
	//
	//// スカイドームクラス
	//skyDome = new SphereMap();
	//skyDome->Init(device, deviceContext, swapChain);

	return S_OK;
}
//
//
//アプリケーション処理。アプリのメイン関数。
void MAIN::App()
{
	// キー操作更新処理
	//key.KeyStateUpdate();

	//camera->Update();
	//sceneManager->Update();
	//sceneManager->Draw();

	Render();
}
//
//
//
void MAIN::DestroyD3D()
{
	//SAFE_RELEASE(swapChain);
	//SAFE_RELEASE(rtv);
	//SAFE_RELEASE(dsv);
	//SAFE_RELEASE(ds);
	//SAFE_RELEASE(device);
}
//
//
//シーンを画面にレンダリング
void MAIN::Render()
{
	//XMMATRIX mView;
	//XMMATRIX mProj;
	////画面クリア（実際は単色で画面を塗りつぶす処理）
	//float ClearColor[4] = { 0,0,1,1 };// クリア色作成　RGBAの順
	//deviceContext->ClearRenderTargetView(rtv, ClearColor);//画面クリア
	//deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);	//深度バッファクリア
	
	// 座標変換
	//camera->Render();

	// フレームレート計算・描画
	//fps->Render();

	// Objファイル（手） 
	//testObj->Render(camera->GetView(), camera->GetProj());

	// スカイドーム描画
	//skyDome->Render(testObj->GetPosition(), camera->GetView(), camera->GetProj());

	//画面更新（バックバッファをフロントバッファに）
	//swapChain->Present(1, 0);//テキストの後(執筆
}