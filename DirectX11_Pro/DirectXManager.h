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
	DirectXManager(const HWND& inHwnd);
	~DirectXManager();

	HRESULT CreateRencerTargetAndDepthStencil();
	HRESULT CreateDepthStencilView();
	//HRESULT CreateSwapChain(const HWND& hwnd);
	HRESULT CreateSwapChain();
	void	SettingViewport();
	void	SettingRasterizer();

	//ComPtr<ID3D11Device> GetDevice() const { return device; }
	//ComPtr<ID3D11DeviceContext> GetDeviceContext() const { return deviceContext; }
	//ComPtr<IDXGISwapChain> GetSwapChain() const { return swapChain; }

	//ComPtr<ID3D11RenderTargetView> GetRtv() const { return rtv; }
	//ComPtr<ID3D11DepthStencilView> GetDsv() const { return dsv; }

	ID3D11Device* GetDevice() const { return device; }
	ID3D11DeviceContext* GetDeviceContext() const { return deviceContext; }
	IDXGISwapChain* GetSwapChain() const { return swapChain; }

	ID3D11RenderTargetView* GetRtv() const { return rtv; }
	ID3D11DepthStencilView* GetDsv() const { return dsv; }

private:
	HWND hWnd;
	//ComPtr<ID3D11Device> device = nullptr;
	//ComPtr<ID3D11DeviceContext> deviceContext = nullptr;
	//ComPtr<IDXGISwapChain> swapChain = nullptr;
	//ComPtr<ID3D11RenderTargetView> rtv = nullptr;
	//ComPtr<ID3D11DepthStencilView> dsv = nullptr;
	//ComPtr<ID3D11DepthStencilState> depthStencilState = nullptr;
	//ComPtr<ID3D11Texture2D> texture = nullptr;

	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* deviceContext = nullptr;
	IDXGISwapChain* swapChain = nullptr;
	ID3D11RenderTargetView* rtv = nullptr;
	ID3D11DepthStencilView* dsv = nullptr;
	ID3D11DepthStencilState* depthStencilState = nullptr;
	ID3D11Texture2D* texture = nullptr;
	
	//HRESULT InitWinow();
};

