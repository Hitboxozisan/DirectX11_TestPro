#pragma once
#include "SceneManager.h"

class SceneBase;
class Text;
class Fps;
class Light;
class TestPolygon;
class PointSprite3D;
class TestObj;
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

	Text* text;				//�����\���p
	Fps* fps;
	Light* light;			// ���C�g
	TestPolygon* polygon;
	PointSprite3D* pointSprite;
	TestObj* testObj;
	Camera* camera;
	SphereMap* skyDome;

};

