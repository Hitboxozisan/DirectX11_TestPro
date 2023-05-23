#pragma once
#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// DirectX11ÇÃê›íËÇçsÇ§ÉNÉâÉX
/// </summary>
class DirectXManager
{
public:
	DirectXManager(HWND inHwnd);
	~DirectXManager();

	//LRESULT MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
	HRESULT CreateRencerTargetAndDepthStencil();
	HRESULT CreateDepthStencilView();
	HRESULT CreateSwapChain(const HWND& hwnd);
	void	SettingViewport();
	void	SettingRasterizer();

	ComPtr<ID3D11Device> GetDevice() const { return device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return deviceContext; }
	ComPtr<IDXGISwapChain> GetSwapChain() const { return swapChain; }

private:
	HWND hWnd;
	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;
	ComPtr<ID3D11RenderTargetView> rtv;
	ComPtr<ID3D11DepthStencilView> dsv;
	ComPtr<ID3D11DepthStencilState> depthStencilState;
	ComPtr<ID3D11Texture2D> ds;

	//HRESULT InitWinow();
	
};

