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
	// 処理なし
}

PlayerDirection::~PlayerDirection()
{
	// 処理なし
}

HRESULT PlayerDirection::Init()
{
	param.pos = INITIAL_POS;

	// objファイルの読み込み
	//char* file = strdup(FILE_PATH[ObjModelType::Player].c_str());
	if (FAILED(meshMgr.LoadMesh(ObjModelType::PlayerDir)))
	{
		MessageBox(0, L"プレイヤーObjファイル読み込み失敗", NULL, MB_OK);
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

	// シェーダーファイルの読み込み
	if (FAILED(shaderMgr.Load(ObjModelType::PlayerDir)))
	{
		MessageBox(0, L"プレイヤーシェーダーファイル読み込み失敗", NULL, MB_OK);
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
