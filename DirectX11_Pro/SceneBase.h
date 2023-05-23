#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class SceneManager;
class D11Device;

/// <summary>
/// �V�[���x�[�X�N���X
/// �e�V�[���N���X�͂��̃N���X���p������
/// </summary>
class SceneBase
{
public:
	SceneBase(SceneManager* const sceneManager);
	virtual ~SceneBase();

	virtual void Initialize() = 0;	//����������
	virtual void Finalize() = 0;	//�I������
	virtual void Activate() = 0;	//����������
	virtual void Deactivate() = 0;	//�񊈐�������
	virtual void Update() = 0;		//�X�V����
	virtual void Draw() = 0;		//�`�揈��

	//void SetGameLevel(const GameLevel level);
	//const GameLevel GetGameLevel() const { return gameLevel; }

protected:
	SceneManager* const parent;
	//GameLevel* const gameLevel;
private:
	SceneBase();						//�f�t�H���g�R���X�g���N�^
	SceneBase(const SceneBase&);		//�R�s�[�R���X�g���N�^
	void operator=(const SceneBase&);	//�R�s�[������Z�q
};

