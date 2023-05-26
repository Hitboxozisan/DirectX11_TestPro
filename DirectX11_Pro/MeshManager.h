#pragma once

#include "Common.h"
#include "Framework.h"
#include "D11Device.h"

using namespace DirectX;

/// <summary>
/// ���b�V���Ǘ��E�ǂݍ��݃N���X
/// �V���O���g��
/// </summary>
class MeshManager
{
public:
	MeshManager();
	~MeshManager();

	struct Mesh;

	 HRESULT LoadMesh(LPSTR fileName);

private:

	// ���b�V���\����
	struct Mesh
	{
		DWORD dwNumVert = 0;
		DWORD dwNumFace = 0;
		ID3D11Buffer* pVertexBuffer;
		ID3D11Buffer* pIndexBuffer;
	};

	struct ObjVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// �ʒu
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	D11Device& device;
	Mesh mesh;
};

