#pragma once
#include "SceneManager.h"

class SceneBase;

/// <summary>
/// �^�C�g�����
/// </summary>
class SceneTitle final : public SceneBase
{
public:
	SceneTitle(SceneManager* const sceneManager);
	~SceneTitle();

	void Initialize() override;	//����������
	void Finalize() override;	//�I������
	void Activate() override;	//����������
	void Deactivate() override;	//�񊈐�������
	void Update() override;		//�X�V����
	void Draw() override;		//�`�揈��

private:


};

