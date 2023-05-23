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
	//device = inDevice;

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
	swapChain = device.dx11->GetSwapChain();

	camera->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void SceneGame::Draw()
{
	camera->Render();
	testObj->Render(camera->GetView(), camera->GetProj());

	//��ʍX�V�i�o�b�N�o�b�t�@���t�����g�o�b�t�@�Ɂj
	swapChain->Present(1, 0);//�e�L�X�g�̌�(���M
}
