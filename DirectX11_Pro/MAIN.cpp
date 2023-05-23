
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

//�O���[�o���ϐ�
//MAIN* g_pMain = NULL;
class Application* app = NULL;
//�֐��v���g�^�C�v�̐錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//
//
//�A�v���P�[�V�����̃G���g���[�֐� 
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	app = new Application(hInstance);
	app->Run();

	//g_pMain = new MAIN;
	//if (g_pMain != NULL)
	//{
	//	if (SUCCEEDED(g_pMain->InitWindow(hInstance, 0, 0, WINDOW_WIDTH,
	//		WINDOW_HEIGHT, APP_NAME)))
	//	{
	//		if (SUCCEEDED(g_pMain->Init()))
	//		{
	//			g_pMain->Loop();
	//		}
	//	}
	//	//�A�v���I��
	//	g_pMain->DestroyD3D();
	//	delete g_pMain;
	//}
	//return 0;
}
//
//
//OS���猩���E�B���h�E�v���V�[�W���[�i���ۂ̏�����MAIN�N���X�̃v���V�[�W���[�ŏ����j
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return app->MsgProc(hWnd, uMsg, wParam, lParam);
}
//
//
//�E�B���h�E�쐬
//HRESULT MAIN::InitWindow(HINSTANCE hInstance,
//	INT iX, INT iY, INT iWidth, INT iHeight, LPCWSTR WindowName)
//{
//	// �E�B���h�E�̒�`
//	WNDCLASSEX  wc;
//	ZeroMemory(&wc, sizeof(wc));
//	wc.cbSize = sizeof(wc);
//	wc.style = CS_HREDRAW | CS_VREDRAW;
//	wc.lpfnWndProc = WndProc;
//	wc.hInstance = hInstance;
//	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
//	wc.lpszClassName = WindowName;
//	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//	RegisterClassEx(&wc);
//
//	//�E�B���h�E�̍쐬
//	hWnd = CreateWindow(WindowName, WindowName, WS_OVERLAPPEDWINDOW,
//		0, 0, iWidth, iHeight, 0, 0, hInstance, 0);
//	if (!hWnd)
//	{
//		return E_FAIL;
//	}
//	//�E�C���h�E�̕\��
//	ShowWindow(hWnd, SW_SHOW);
//	UpdateWindow(hWnd);
//
//	return S_OK;
//}
//
//
//�E�B���h�E�v���V�[�W���[
//LRESULT MAIN::MsgProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//{
//	switch (iMsg)
//	{
//	case WM_KEYDOWN:
//		switch ((char)wParam)
//		{
//		case VK_ESCAPE://ESC�L�[�ŏC��
//			PostQuitMessage(0);
//			break;
//		}
//		break;
//	case WM_DESTROY:
//		PostQuitMessage(0);
//		break;
//	}
//	return DefWindowProc(hWnd, iMsg, wParam, lParam);
//}

/// <summary>
/// ����������
/// </summary>
//HRESULT MAIN::Init()
//{
//	
//
//	//key = Singleton<KeyManager>::GetInstance();
//
//	//light = new Light;
//	//light->SetLight({ 0.0f, 0.0f, 5.0f, -1.0f });
//	//light->SetLight(XMVector3Normalize(light->GetLight()));
//
//	if (FAILED(InitD3D()))
//	{
//		return E_FAIL;
//	}
//
//	// �V�[���Ǘ�
//	// �����͌�ɏC��
//	//sceneManager = new SceneManager();
//	//sceneManager->Initialize();
//
//	return S_OK;
//}
//
//
//���b�Z�[�W���[�v�ƃA�v���P�[�V���������̓����
//void MAIN::Loop()
//{
//	// ���b�Z�[�W���[�v
//	MSG msg = { 0 };
//	ZeroMemory(&msg, sizeof(msg));
//	while (msg.message != WM_QUIT)
//	{
//		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//		{
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		else
//		{
//			//�A�v���P�[�V�����̏����͂��������ԁB
//			App();
//		}
//	}
//	//�A�v���P�[�V�����̏I��
//}
//
//
//
//HRESULT MAIN::InitD3D()
//{
//	HRESULT result;
//
//	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
//	DXGI_SWAP_CHAIN_DESC sd;
//	ZeroMemory(&sd, sizeof(sd));
//	sd.BufferCount = 1;
//	sd.BufferDesc.Width = WINDOW_WIDTH;
//	sd.BufferDesc.Height = WINDOW_HEIGHT;
//	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	sd.BufferDesc.RefreshRate.Numerator = FLAME_RATE;
//	sd.BufferDesc.RefreshRate.Denominator = 1;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.OutputWindow = hWnd;
//	sd.SampleDesc.Count = 1;
//	sd.SampleDesc.Quality = 0;
//	sd.Windowed = TRUE;
//
//	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
//	D3D_FEATURE_LEVEL* pFeatureLevel = NULL;
//
//	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL,
//		0, &pFeatureLevels, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device,
//		pFeatureLevel, &deviceContext)))
//	{
//		return FALSE;
//	}
//
//
//	//�����_�[�^�[�Q�b�g�r���[�̍쐬
//	ID3D11Texture2D* pBackBuffer = nullptr;
//	swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
//	// ���̃e�N�X�`���[�ɑ΂������_�[�^�[�Q�b�g�r���[���쐬
//	if (FAILED(device->CreateRenderTargetView(pBackBuffer, NULL, &rtv)))
//	{
//		return E_FAIL;
//	}
//	SAFE_RELEASE(pBackBuffer);
//
//	//�[�x�X�e���V���r���[�̍쐬
//	D3D11_TEXTURE2D_DESC descDepth;
//	descDepth.Width = WINDOW_WIDTH;
//	descDepth.Height = WINDOW_HEIGHT;
//	descDepth.MipLevels = 1;
//	descDepth.ArraySize = 1;
//	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
//	descDepth.SampleDesc.Count = 1;
//	descDepth.SampleDesc.Quality = 0;
//	descDepth.Usage = D3D11_USAGE_DEFAULT;
//	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//	descDepth.CPUAccessFlags = 0;
//	descDepth.MiscFlags = 0;
//	result = device->CreateTexture2D(&descDepth, NULL, &ds);
//	if (FAILED(result))
//	{
//		return E_FAIL;
//	}
//	// ���̃e�N�X�`���[�ɑ΂��f�v�X�X�e���V���r���[���쐬
//	result = device->CreateDepthStencilView(ds, NULL, &dsv);
//	if (FAILED(result))
//	{
//		return E_FAIL;
//	}
//
//	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ƀo�C���h
//	deviceContext->OMSetRenderTargets(1, &rtv, dsv);
//	
//
//	// �[�x�e�X�g�𖳌��ɂ���
//	//D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
//	//ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
//	//depthStencilDesc.DepthEnable = false;
//	//
//	//device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
//	//deviceContext->OMSetDepthStencilState(depthStencilState, 1);
//
//	//�r���[�|�[�g�̐ݒ�
//	//D3D11_VIEWPORT vp;
//	//vp.Width = WINDOW_WIDTH;
//	//vp.Height = WINDOW_HEIGHT;
//	//vp.MinDepth = 0.0f;
//	//vp.MaxDepth = 1.0f;
//	//vp.TopLeftX = 0;
//	//vp.TopLeftY = 0;
//	//deviceContext->RSSetViewports(1, &vp);
//	//���X�^���C�Y�ݒ�
//	//D3D11_RASTERIZER_DESC rdc;
//	//ZeroMemory(&rdc, sizeof(rdc));
//	//rdc.CullMode = D3D11_CULL_NONE;
//	//rdc.FillMode = D3D11_FILL_SOLID;
//	//ID3D11RasterizerState* pIr = NULL;
//	//device->CreateRasterizerState(&rdc, &pIr);
//	//deviceContext->RSSetState(pIr);
//	//SAFE_RELEASE(pIr);
//
//
//	// Xinput��������
//	//XInputEnable(true);
//
//	// �e�C���X�^���X����
//
//	//�����񃌃��_�����O�̏�����
//	//text = new Text;
//	//XMFLOAT4 vColor(1.0f, 0.0f, 0.0f, 1.0f);
//	//if (FAILED(text->Init(deviceContext, WINDOW_WIDTH, WINDOW_HEIGHT, 25, vColor)))
//	//{
//	//	return E_FAIL;
//	//}
//	// �t���[�����[�g
//	//fps = new Fps;
//	//fps->Init(text);
//
//	//testObj = new TestObj;
//	//testObj->Init(device, deviceContext, swapChain);
//	//
//	//// �J�����N���X
//	//camera = new Camera();
//	//camera->Init();
//	//
//	//// �X�J�C�h�[���N���X
//	//skyDome = new SphereMap();
//	//skyDome->Init(device, deviceContext, swapChain);
//
//	return S_OK;
//}
//
//
//�A�v���P�[�V���������B�A�v���̃��C���֐��B
//void MAIN::App()
//{
//	// �L�[����X�V����
//	//key.KeyStateUpdate();
//
//	//camera->Update();
//	sceneManager->Update();
//	sceneManager->Draw();
//
//	Render();
//}
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
//�V�[������ʂɃ����_�����O
void MAIN::Render()
{
	//XMMATRIX mView;
	//XMMATRIX mProj;
	////��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	//float ClearColor[4] = { 0,0,1,1 };// �N���A�F�쐬�@RGBA�̏�
	//deviceContext->ClearRenderTargetView(rtv, ClearColor);//��ʃN���A
	//deviceContext->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH, 1.0f, 0);	//�[�x�o�b�t�@�N���A
	
	// ���W�ϊ�
	//camera->Render();

	// �t���[�����[�g�v�Z�E�`��
	//fps->Render();

	// Obj�t�@�C���i��j 
	//testObj->Render(camera->GetView(), camera->GetProj());

	// �X�J�C�h�[���`��
	//skyDome->Render(testObj->GetPosition(), camera->GetView(), camera->GetProj());

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	//swapChain->Present(1, 0);//�e�L�X�g�̌�(���M
}