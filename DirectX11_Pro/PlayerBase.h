#pragma once
#include "Common.h"
#include "Framework.h"
#include "Collision.h"
#include "CollisionTag.h"

using namespace DirectX;
using namespace Tag;

class PlayerBase
{
public:
	PlayerBase();
	virtual ~PlayerBase();

	// ���W
	const XMFLOAT3 GetPosition() { return param.pos; };
	// �����蔻��^�O
	const CollisionTag GetTag() { return param.tag; };
	// �����蔻�菈��
	virtual void OnCollisionEnter(class Collision* other);

	class Collision* GetCollision() { return param.collision; };

protected:
	// �v���C���[�̃X�e�[�^�X
	struct Param
	{
		XMFLOAT3 pos;
		class Collision* collision;
		CollisionTag tag;
	};

	Param param;
	bool isExist;

	// �G�t�F�N�g�Ǘ��N���X

private:

};

