#include "Player.h"
#include "Singleton.h"
#include "MathDx11.h"
//#include "ModelData.h"
#include "D11Device.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "ShaderManager.h"


// xmfloat,xmmatrix�֌W�̉��Z�����Ɏg�p
using namespace MathDx11;
// ���f���̃t�@�C���p�X���o���Ɏg�p
//using namespace ObjModelData;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
	:device(Singleton<D11Device>::GetInstance())
	,meshMgr(Singleton<MeshManager>::GetInstance())
	,shaderMgr(Singleton<ShaderManager>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,camera(Singleton<Camera>::GetInstance())
	,isAlive(true)
{
	// �����Ȃ�
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

	//// obj�t�@�C���̓ǂݍ���
	//char* file = strdup(FILE_PATH[ObjModelType::Player].c_str());
	//if (FAILED(meshMgr.LoadMesh(file)))
	//{
	//	MessageBox(0, L"�v���C���[Obj�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
	//	return;
	//}
	//mesh.vertexBuffer = meshMgr.GetVertexBuffer();
	//mesh.indexBuffer = meshMgr.GetIndexBuffer();
	//material.kd = meshMgr.mateMgr.GetDiffuse();
	//material.ks = meshMgr.mateMgr.GetSpecular();
	//texture = meshMgr.mateMgr.GetTexture();
	//sampleLinear = meshMgr.mateMgr.GetSmpleLinear();
	//
	//// �V�F�[�_�[�t�@�C���̓ǂݍ���
	//if (FAILED(shaderMgr.Load(ObjModelType::Player)))
	//{
	//	MessageBox(0, L"�v���C���[�V�F�[�_�[�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
	//	return;
	//}
	//vertexShader = shaderMgr.GetVertexShader();
	//pixelShader = shaderMgr.GetPixelShader();
	//vertexLayout = shaderMgr.GetVertexLayout();
	//constantBuffer = shaderMgr.GetConstantBuffer();

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
	XMMATRIX position, mTran, mYaw, mPitch, mRoll, mScale;
	position = ConvertXMFLOAT3FromXMMATRIX(param.pos);
	position = XMMatrixRotationY(0.0f);
	mScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	mYaw = XMMatrixRotationY(0.0f);
	mPitch = XMMatrixRotationX(0.0f);
	mRoll = XMMatrixRotationZ(0.0f);
	mTran = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	position = mScale * mYaw * mPitch * mRoll * mTran;

	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	//mWorld = XMMatrixRotationY(timeGetTime() / 1100.0f);//�P����yaw��]������

	//�g�p����V�F�[�_�[�̓o�^	
	device.dx11->GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
	device.dx11->GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	ShaderConstantBuffer cb;
	if (SUCCEEDED(device.dx11->GetDeviceContext()->Map(mesh.vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// ���[���h�s��
		cb.W = position;
		cb.W = XMMatrixTranspose(cb.W);
		//���[���h�A�J�����A�ˉe�s���n��
		XMMATRIX m = position * camera.GetView() * camera.GetProj();
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);
		// ���C�g�̕�����n��
		XMFLOAT3 lightDir = { -1.0f, 0.0f, -1.0f };
		cb.lightDir = XMFLOAT4(lightDir.x, lightDir.y, lightDir.z, 0.0f);
		// �f�B�t���[�Y�J���[��n��
		cb.diffuse = material.kd;
		// �X�y�L�����[���V�F�[�_�[�ɓn��
		cb.specular = material.ks;
		// �J�����ʒu���V�F�[�_�[�ɓn��
		cb.eye = XMFLOAT4(camera.GetPos().x, camera.GetPos().y, camera.GetPos().z, 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderConstantBuffer));
		device.dx11->GetDeviceContext()->Unmap(constantBuffer, 0);
	}
	// �e�N�X�`�����V�F�[�_�[�ɓn��
	//device.dx11->GetDeviceContext()->PSSetSamplers(0, 1, &sampleLinear);
	//device.dx11->GetDeviceContext()->PSSetShaderResources(0, 1, &texture);
	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	device.dx11->GetDeviceContext()->VSSetConstantBuffers(0, 1, &constantBuffer);
	device.dx11->GetDeviceContext()->PSSetConstantBuffers(0, 1, &constantBuffer);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	device.dx11->GetDeviceContext()->IASetInputLayout(vertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	device.dx11->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(ObjVertex);
	UINT offset = 0;
	device.dx11->GetDeviceContext()->IASetVertexBuffers(0, 1, &mesh.vertexBuffer, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	device.dx11->GetDeviceContext()->IASetIndexBuffer(mesh.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//�v���~�e�B�u�������_�����O
	device.dx11->GetDeviceContext()->DrawIndexed(mesh.dwNumFace * 3, 0, 0);
}

/// <summary>
/// �����蔻��`��
/// </summary>
/// <param name="other"></param>
void Player::OnCollisionEnter(Collision* other)
{
}

/// <summary>
/// �ړ�����
/// </summary>
void Player::Move()
{
	// �O�����x�N�g�����o��
	XMFLOAT3 Forward = SubXMFLOAT3(param.pos, camera.GetPos());
	// ���ɂ߂荞�񂾂肷��̂�h������Y����0�ɂ���
	Forward.y = 0;

}
