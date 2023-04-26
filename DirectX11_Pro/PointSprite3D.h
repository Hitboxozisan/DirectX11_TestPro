#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// �|�C���g�X�v���C�g��3D��Ԃŕ`�悷��
/// </summary>
class PointSprite3D
{
public:
	PointSprite3D();
	~PointSprite3D();

	HRESULT Init();
	HRESULT InitModel();
	HRESULT MakeShader();
	void Render();

private:
	//���_�̍\����
	struct PointSprite3DVertex
	{
		XMFLOAT3 Pos; //�ʒu
	};
	//�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
	struct PointSprite3DBuffer
	{
		XMMATRIX mWVP;
	};


};

