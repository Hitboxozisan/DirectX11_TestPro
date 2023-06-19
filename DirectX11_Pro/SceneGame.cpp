#include "SceneGame.h"
#include "D11Device.h"
#include "Camera.h"
#include "Text.h"
#include "TestObj.h"
#include "Singleton.h"
#include "Light.h"
#include "Player.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="sceneManager"></param>
SceneGame::SceneGame(SceneManager* const sceneManager)
	:SceneBase(sceneManager)
	,device(Singleton<D11Device>::GetInstance())
	,camera(Singleton<Camera>::GetInstance())
	,text(Singleton<Text>::GetInstance())
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
	testObj = new TestObj();
	player = new Player();

	//light->SetLight({ 0.0f, 0.0f, 5.0f, -1.0f });
	//light->SetLight(XMVector3Normalize(light->GetLight()));
	//text.Init(WINDOW_WIDTH, WINDOW_HEIGHT, 23, XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	camera.Init();
	testObj->Init();
	player->Init();
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
	camera.Update();
	camera.FollowUpPlayer(player->GetPos());
	player->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneGame::Draw()
{
	XMMATRIX mView;
	XMMATRIX mProj;

	//��ʃN���A�i���ۂ͒P�F�ŉ�ʂ�h��Ԃ������j
	float ClearColor[4] = { 0, 0, 0.5, 1 };// �N���A�F�쐬�@RGBA�̏�
	device.dx11->GetDeviceContext()->ClearRenderTargetView(device.dx11->GetRtv(), ClearColor);					//��ʃN���A
	device.dx11->GetDeviceContext()->ClearDepthStencilView(device.dx11->GetDsv(), D3D11_CLEAR_DEPTH, 1.0f, 0);	//�[�x�o�b�t�@�N���A

	//text.Render("ABC", 50, 50);

	camera.Render();
	testObj->Render();
	player->Draw();


	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	device.dx11->GetSwapChain()->Present(1, 0);
}
