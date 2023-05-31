#pragma once

#include "Common.h"
#include "Framework.h"
#include "ModelTypeData.h"

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

	 HRESULT LoadMesh(ObjModelType inType);

	 DWORD GetNumVert() const { return mesh.dwNumVert; }
	 DWORD GetNumFace() const { return mesh.dwNumFace; }
	 ID3D11Buffer* GetVertexBuffer() const { return mesh.vertexBuffer; }
	 ID3D11Buffer* GetIndexBuffer() const { return mesh.indexBuffer; }

	class MaterialManager& mateMgr;
private:

	// ���b�V���\����
	struct Mesh
	{
		DWORD dwNumVert = 0;
		DWORD dwNumFace = 0;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	};

	struct ObjVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// �ʒu
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	class D11Device& device;
	
	Mesh mesh;
};

