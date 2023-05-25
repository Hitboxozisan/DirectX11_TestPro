#include "SceneGame.h"
#include "D11Device.h"
#include "Camera.h"
#include "TestObj.h"
#include "Singleton.h"
#include "Light.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
SceneGame::SceneGame(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,device(Singleton<D11Device>::GetInstance())
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
	light = new Light();
	camera = new Camera();
	testObj = new TestObj();

	//light->SetLight({ 0.0f, 0.0f, 5.0f, -1.0f });
	//light->SetLight(XMVector3Normalize(light->GetLight()));
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
	device.dx11->GetDeviceContext()->ClearRenderTargetView(device.dx11->GetRtv().Get(), ClearColor);					//��ʃN���A
	device.dx11->GetDeviceContext()->ClearDepthStencilView(device.dx11->GetDsv().Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);	//�[�x�o�b�t�@�N���A

	//camera->Render();
	//testObj->Render(camera->GetView(), camera->GetProj());

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	device.dx11->GetSwapChain()->Present(1, 0);
}
