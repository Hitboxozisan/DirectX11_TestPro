#include "Player.h"
#include "Singleton.h"
#include "MathDx11.h"
#include "D11Device.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "ShaderManager.h"

// xmfloat,xmmatrix�֌W�̉��Z�����Ɏg�p
using namespace MathDx11;

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
	param.dir = XMFLOAT3(0, 0, 0);

	axisX = XMVECTOR{ 1, 0, 0 };
	axisY = XMVECTOR{ 0, 1, 0 };
	axisZ = XMVECTOR{ 0, 0, 1 };

	yaw = 1.0f;

	// obj�t�@�C���̓ǂݍ���
	//char* file = strdup(FILE_PATH[ObjModelType::Player].c_str());
	if (FAILED(meshMgr.LoadMesh(ObjModelType::Player)))
	{
		MessageBox(0, L"�v���C���[Obj�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
		return;
	}
	mesh.dwNumVert = meshMgr.GetNumVert();
	mesh.dwNumFace = meshMgr.GetNumFace();
	mesh.vertexBuffer = meshMgr.GetVertexBuffer();
	mesh.indexBuffer = meshMgr.GetIndexBuffer();
	material.kd = meshMgr.mateMgr.GetDiffuse();
	material.ks = meshMgr.mateMgr.GetSpecular();
	texture = meshMgr.mateMgr.GetTexture();
	sampleLinear = meshMgr.mateMgr.GetSmpleLinear();
	
	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	if (FAILED(shaderMgr.Load(ObjModelType::Player)))
	{
		MessageBox(0, L"�v���C���[�V�F�[�_�[�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
		return;
	}
	vertexShader = shaderMgr.GetVertexShader();
	pixelShader = shaderMgr.GetPixelShader();
	vertexLayout = shaderMgr.GetVertexLayout();
	constantBuffer = shaderMgr.GetConstantBuffer();

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
	Move();
}

/// <summary>
/// �`�揈��
/// </summary>
void Player::Draw()
{
	view = camera.GetView();
	proj = camera.GetProj();
	eye = { 0.0f, 0.0f, -1.0f };

	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	device.dx11->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	XMMATRIX position, tran, rot, mScale;
	tran = XMMatrixTranslation(param.pos.x, param.pos.y, param.pos.z);
	rot = XMMatrixRotationY(yaw);
	axisX = XMVector3TransformCoord(XMVECTOR{ 1, 0, 0 }, rot);
	axisY = XMVector3TransformCoord(XMVECTOR{ 0, 1, 0 }, rot);
	axisZ = XMVector3TransformCoord(XMVECTOR{ 0, 0, 1 }, rot);
	
	//mScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);

	position = rot * tran;

	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	//position = XMMatrixRotationY(timeGetTime() / 1100.0f);//�P����yaw��]������

	DrawMesh(position);
}

/// <summary>
/// �����蔻��`��
/// </summary>
/// <param name="other"></param>
void Player::OnCollisionEnter(Collision* other)
{
}

void Player::DrawMesh(XMMATRIX pos)
{
	XMMATRIX world = pos;

	//�g�p����V�F�[�_�[�̓o�^	
	device.dx11->GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
	device.dx11->GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);

	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	ShaderConstantBuffer cb;
	if (SUCCEEDED(device.dx11->GetDeviceContext()->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// ���[���h�s��
		cb.W = world;
		cb.W = XMMatrixTranspose(cb.W);
		//���[���h�A�J�����A�ˉe�s���n��
		cb.WVP = world * view * proj;
		cb.WVP = XMMatrixTranspose(cb.WVP);
		// ���C�g�̕�����n��
		XMFLOAT3 lightDir = { -1.0f, 0.0f, -1.0f };
		cb.lightDir = XMFLOAT4(lightDir.x, lightDir.y, lightDir.z, 0.0f);
		// �f�B�t���[�Y�J���[��n��
		cb.diffuse = material.kd;
		// �X�y�L�����[���V�F�[�_�[�ɓn��
		cb.specular = material.ks;
		// �J�����ʒu���V�F�[�_�[�ɓn��
		cb.eye = XMFLOAT4(eye.x, eye.y, eye.z, 0.0f);

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
/// �ړ�����
/// </summary>
void Player::Move()
{
	// �O�����x�N�g�����o��
	XMFLOAT3 Forward = SubXMFLOAT3(param.pos, camera.GetPos());
	// ���ɂ߂荞�񂾂肷��̂�h������Y����0�ɂ���
	Forward.y = 0;
	// ���K��
	Forward = NormalizeXMFLOAT3(Forward);

	// �O�ς��牡�̃x�N�g�����擾
	XMFLOAT3 right = CrossXMFLOAT3(XMFLOAT3(0, 1, 0), Forward);

	// ���̓x�N�g��
	XMFLOAT3 inputVec(0, 0, 0);
	
	// ���ۂ̓��͒l
	XMFLOAT2 input(0, 0);

	// �L�[�{�[�h
	//param.pos.x += -(key.IsKeyPush(KeyInfo::KeyMoveLeft)) * 0.1 + (key.IsKeyPush(KeyInfo::KeyMoveRight)) * 0.1;
	//param.pos.z += -(key.IsKeyPush(KeyInfo::KeyMoveBack)) * 0.1 + (key.IsKeyPush(KeyInfo::KeyMoveForward)) * 0.1;
	
	if (key.IsKeyPush(KeyInfo::KeyMoveForward)) input.y += 1;
	if (key.IsKeyPush(KeyInfo::KeyMoveBack)) input.y += -1;
	if (key.IsKeyPush(KeyInfo::KeyMoveRight)) input.x += 1;
	if (key.IsKeyPush(KeyInfo::KeyMoveLeft)) input.x += -1;

	inputVec += ScaleXMFLOAT3(Forward, input.y * 0.1);
	inputVec += ScaleXMFLOAT3(right, input.x * 0.1);

	param.pos += inputVec;

	// ��]
	yaw += -(key.IsKeyPush(KeyInfo::KeyRotateL)) * 0.1f + (key.IsKeyPush(KeyInfo::KeyRotateR)) * 0.1f;

	// �R���g���[���[
	// �R���g���[���[�̓��͂��擾
	input = key.GetLStickInput();
	inputVec += ScaleXMFLOAT3(Forward, input.y * 10);
	inputVec += ScaleXMFLOAT3(right, input.x * 10);

	param.pos += inputVec;
}
