#include "PlayerDirection.h"
#include "Singleton.h"
#include "D11Device.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "MaterialManager.h"

PlayerDirection::PlayerDirection()
	:device(Singleton<D11Device>::GetInstance())
	,meshMgr(Singleton<MeshManager>::GetInstance())
	,shaderMgr(Singleton<ShaderManager>::GetInstance())
{
	// �����Ȃ�
}

PlayerDirection::~PlayerDirection()
{
	// �����Ȃ�
}

HRESULT PlayerDirection::Init()
{
	param.pos = INITIAL_POS;

	// obj�t�@�C���̓ǂݍ���
	//char* file = strdup(FILE_PATH[ObjModelType::Player].c_str());
	if (FAILED(meshMgr.LoadMesh(ObjModelType::PlayerDir)))
	{
		MessageBox(0, L"�v���C���[Obj�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
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
	if (FAILED(shaderMgr.Load(ObjModelType::PlayerDir)))
	{
		MessageBox(0, L"�v���C���[�V�F�[�_�[�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	vertexShader = shaderMgr.GetVertexShader();
	pixelShader = shaderMgr.GetPixelShader();
	vertexLayout = shaderMgr.GetVertexLayout();
	constantBuffer = shaderMgr.GetConstantBuffer();

	return S_OK;
}

void PlayerDirection::Update()
{

}

void PlayerDirection::Draw()
{
}
