#include "Player.h"
#include "Singleton.h"
#include "MathDx11.h"
#include "Camera.h"
#include "KeyManager.h"

using namespace MathDx11;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	:key(Singleton<KeyManager>::GetInstance())
	,camera(Singleton<Camera>::GetInstance())
	,isAlive(true)
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	// �e��I���������s
	Fainalize();
}

/// <summary>
/// ����������
/// </summary>
void Player::Init()
{
	param.pos = INITIAL_POS;
}

/// <summary>
/// �I������
/// </summary>
void Player::Fainalize()
{
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update()
{
	//Move();
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
}

/// <summary>
/// �����蔻��`��
/// </summary>
/// <param name="other"></param>
void Player::OnCollisionEnter(Collision* other)
{
}

void Player::Move()
{
	// �O�����x�N�g�����o��
	XMFLOAT3 Forward = SubXMFLOAT3(param.pos, camera.GetPos());
	// ���ɂ߂荞�񂾂肷��̂�h������Y����0�ɂ���
	Forward.y = 0;

}
