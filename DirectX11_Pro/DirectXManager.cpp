#include "DirectXManager.h"

DirectXManager::DirectXManager(HWND inHwnd)
	:hWnd(inHwnd)
{
	// �����Ȃ�
}

DirectXManager::~DirectXManager()
{
	// �����Ȃ�
}

HRESULT DirectXManager::CreateRencerTarget()
{
	ID3D11Texture2D* pBackBuffer = nullptr;
	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	// ���̃e�N�X�`���[�ɑ΂������_�[�^�[�Q�b�g�r���[���쐬
	if (FAILED(device->CreateRenderTargetView(pBackBuffer, NULL, &rtv)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pBackBuffer);

	// �[�x�X�e���V���r���[�̍쐬
	CreateDepthStencilView();

	deviceContext->OMSetRenderTargets(1, &rtv, dsv.Get());

    return S_OK;
}

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

    return S_OK;
}

HRESULT DirectXManager::CreateSwapChain(const HWND& hwnd)
{
	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
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


    return S_OK;
}
