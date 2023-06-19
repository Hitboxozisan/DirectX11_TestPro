#pragma once

#include "common.h"
#include "CollisionTag.h"
#include "Collision.h"

using namespace DirectX;
using namespace Tag;

class Mover
{
public:
	Mover();
	virtual ~Mover();

	virtual void Initialize();

	// �Q�b�^�[
	const XMFLOAT3 GetPos() const { return param.pos; };
	const CollisionTag GetTag() const { return param.tag; };
	const bool GetExist() const { return exist; };

protected:
	// �I�u�W�F�N�g�̃p�����[�^
	struct Param
	{
		XMFLOAT3 pos;			// ���݂̍��W�i���ۂ̕`��ʒu�j
		XMFLOAT3 prevPos;		// 1�t���[���O�̍��W
		XMFLOAT3 nextPos;		// �P�t���[����̍��W�i���̕`��ʒu�j
		XMFLOAT3 dir;
		Collision* collision;
		CollisionTag tag;
	};

	//class DeltaTime& deltaTime;

	Param param;
	//float deltaTime;	// �f���^�^�C��
	bool exist;			// ���݂��邩

	void ModifyingPosition();		// �ʒu���C������
	void MoveFinish();				// ���ۂɃ��f�����ړ�������
private:
};

