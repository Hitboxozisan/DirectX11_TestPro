
#include "Common.h"
#include "Framework.h"
#include "DirectXManager.h"

DirectXManager::DirectXManager(const HWND& inHwnd)
	:hWnd(inHwnd)
{
	// 処理なし
}

DirectXManager::~DirectXManager()
{
	SAFE_RELEASE(device);
	SAFE_RELEASE(deviceContext);
	SAFE_RELEASE(swapChain);
	SAFE_RELEASE(rtv);
	SAFE_RELEASE(dsv);
	SAFE_RELEASE(depthStencilState);
	SAFE_RELEASE(texture);
}

/// <summary>
/// レンダーターゲットビュー作成
/// </summary>
/// <returns></returns>
HRESULT DirectXManager::CreateRencerTargetAndDepthStencil()
{
	ID3D11Texture2D* pBackBuffer = nullptr;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	// そのテクスチャーに対しレンダーターゲットビューを作成
	if (FAILED(device->CreateRenderTargetView(pBackBuffer, NULL, &rtv)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pBackBuffer);

	// 深度ステンシルビューの作成
	if (FAILED(CreateDepthStencilView()))
	{
		return E_FAIL;
	}

	deviceContext->OMSetRenderTargets(1, &rtv, dsv);

    return S_OK;
}

/// <summary>
/// 深度ステンシル作成
/// </summary>
/// <returns></returns>
HRESULT DirectXManager::CreateDepthStencilView()
{
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = WINDOW_WIDTH;
	descDepth.Height = WINDOW_HEIGHT;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;

	if (FAILED(device->CreateTexture2D(&descDepth, NULL, &texture)))
	{
		return E_FAIL;
	}
	// そのテクスチャーに対しデプスステンシルビューを作成
	if (FAILED(device->CreateDepthStencilView(texture, NULL, &dsv)))
	{
		return E_FAIL;
	}

    return S_OK;
}

HRESULT DirectXManager::CreateSwapChain()
{
	// デバイスとスワップチェーンの作成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = WINDOW_WIDTH;
	sd.BufferDesc.Height = WINDOW_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = FLAME_RATE;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device,
		pFeatureLevel, &deviceContext)))
	{
		return E_FAIL;
	}

    return S_OK;
}

void DirectXManager::SettingViewport()
{
	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = WINDOW_WIDTH;
	vp.Height = WINDOW_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &vp);
}

void DirectXManager::SettingRasterizer()
{
	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.CullMode = D3D11_CULL_NONE;
	rdc.FillMode = D3D11_FILL_SOLID;
	ID3D11RasterizerState* pIr = NULL;
	device->CreateRasterizerState(&rdc, &pIr);
	deviceContext->RSSetState(pIr);
	SAFE_RELEASE(pIr);
}
