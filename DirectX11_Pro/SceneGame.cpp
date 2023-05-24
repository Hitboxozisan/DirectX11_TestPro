#include "SceneGame.h"
#include "D11Device.h"
#include "Camera.h"
#include "TestObj.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
SceneGame::SceneGame(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneGame::~SceneGame()
{
}

/// <summary>
/// ����������
/// </summary>
void SceneGame::Initialize()
{
	camera = new Camera();
	testObj = new TestObj();

	camera->Init();
	testObj->Init();
}

/// <summary>
/// �I������
/// </summary>
void SceneGame::Finalize()
{
}

/// <summary>
/// ����������
/// </summary>
void SceneGame::Activate()
{
}

/// <summary>
/// �񊈐�������
/// </summary>
void SceneGame::Deactivate()
{
}

/// <summary>
/// �X�V����
/// </summary>
void SceneGame::Update()
{
	deviceContext = device.dx11->GetDeviceContext().Get();
	swapChain = device.dx11->GetSwapChain();

	camera->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneGame::Draw()
{
	XMMATRIX mView;
	XMMATRIX mProj;
	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0,0,1,1 };// �N���A�F�쐬�@RGBA�̏�
	deviceContext->ClearRenderTargetView(device.dx11->GetRtv().Get(), ClearColor);					//��ʃN���A
	deviceContext->ClearDepthStencilView(device.dx11->GetDsv().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);	//�[�x�o�b�t�@�N���A

	camera->Render();
	testObj->Render(camera->GetView(), camera->GetProj());

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	swapChain->Present(1, 0);//�e�L�X�g�̌�(���M
}
