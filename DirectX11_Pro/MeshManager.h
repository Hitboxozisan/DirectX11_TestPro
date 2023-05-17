#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// メッシュ管理・読み込みクラス
/// シングルトン
/// </summary>
class MeshManager
{
public:
	static MeshManager& GetInstance()
	{
		static MeshManager meshMgr;
		return meshMgr;
	}

	struct Mesh;

	 HRESULT LoadMesh(ID3D11Device* inDevice, LPSTR fileName, Mesh* mesh);

private:
	MeshManager();
	~MeshManager();

	// メッシュ構造体
	struct Mesh
	{
		DWORD dwNumVert = 0;
		DWORD dwNumFace = 0;
		ID3D11Buffer* pVertexBuffer;
		ID3D11Buffer* pIndexBuffer;
	};

	struct ObjVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// 位置
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	Mesh mesh;

};

