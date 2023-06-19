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
	const XMFLOAT3 GetPos() { return param.pos; };
	// ����
	const XMFLOAT3 GetDir() { return param.dir; };
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
		XMFLOAT3 dir;
		class Collision* collision;
		CollisionTag tag;
	};

	// ���b�V���\����
	struct PlayerMesh
	{
		DWORD dwNumVert = 0;
		DWORD dwNumFace = 0;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	};

	// �}�e���A���\����
	struct PlayerMaterial
	{
		//CHAR name[111];
		XMFLOAT4 ka;
		XMFLOAT4 kd;
		XMFLOAT4 ks;
		//CHAR textureName[110];
	};

	struct ObjVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// �ʒu
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	const XMFLOAT3 INITIAL_POS = { 0.0f, 0.0f, 10.0f };

	Param param;
	PlayerMesh mesh;
	PlayerMaterial material;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* constantBuffer;
	ID3D11SamplerState* sampleLinear;		// �e�N�X�`���̃T���v���[
	ID3D11ShaderResourceView* texture;		// �e�N�X�`��

	bool isExist;

	// �G�t�F�N�g�Ǘ��N���X

private:

};

