#pragma once

#include "Common.h"
#include "Framework.h"
#include "D11Device.h"

using namespace DirectX;

/// <summary>
/// メッシュ管理・読み込みクラス
/// シングルトン
/// </summary>
class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	struct Mesh;

	 HRESULT LoadMesh(LPSTR fileName);

private:

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

	D11Device& device;
	Mesh mesh;
};

