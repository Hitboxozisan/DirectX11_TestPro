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

	ComPtr<ID3D11RenderTargetView> GetRtv() const { return rtv; }
	ComPtr<ID3D11DepthStencilView> GetDsv() const { return dsv; }

private:
	HWND hWnd;
	ComPtr<ID3D11Device> device = nullptr;
	ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	ComPtr<IDXGISwapChain> swapChain = nullptr;
	ComPtr<ID3D11RenderTargetView> rtv = nullptr;
	ComPtr<ID3D11DepthStencilView> dsv = nullptr;
	ComPtr<ID3D11DepthStencilState> depthStencilState = nullptr;
	ComPtr<ID3D11Texture2D> ds = nullptr;

	//HRESULT InitWinow();
	
};

