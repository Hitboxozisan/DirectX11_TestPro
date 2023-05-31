#pragma once
#include "Common.h"
#include "Framework.h"
#include "SceneManager.h"
#include "D11Device.h"

class SceneBase;
class Fps;
class Light;
class SphereMap;

/// <summary>
/// �Q�[���V�[��
/// </summary>
class SceneGame final : public SceneBase
{
public:
	SceneGame(SceneManager* const sceneManager);
	~SceneGame();

	void Initialize() override;	//����������
	void Finalize() override;	//�I������
	void Activate() override;	//����������
	void Deactivate() override;	//�񊈐�������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

private:

	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;

	class D11Device& device;
	class Camera& camera;
	class Text& text;					// �����\���p

	Fps* fps;
	class Light* light;			// ���C�g
	class TestObj* testObj;
	class Player* player;		// �v���C���[
	SphereMap* skyDome;

};

