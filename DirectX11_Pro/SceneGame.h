#pragma once
#include "Common.h"
#include "Framework.h"
#include "SceneManager.h"
#include "D11Device.h"

class SceneBase;
class Text;
class Fps;
class Light;
class TestPolygon;
class PointSprite3D;
class Camera;
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

	ComPtr<IDXGISwapChain> swapChain;

	class D11Device device;

	Text* text;				//�����\���p
	Fps* fps;
	Light* light;			// ���C�g
	TestPolygon* polygon;
	PointSprite3D* pointSprite;
	class TestObj* testObj;
	Camera* camera;
	SphereMap* skyDome;

};

