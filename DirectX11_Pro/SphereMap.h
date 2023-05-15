#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

struct SphereMapMesh
{
	DWORD dwNumVert = 0;
	DWORD dwNumFace = 0;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};

struct SphereMapMaterial
{
	CHAR name[111];
	XMFLOAT4 ka;
	XMFLOAT4 kd;
	XMFLOAT4 ks;
	CHAR textureName[110];
};


/// <summary>
/// ���}�b�s���O�i�X�t�B�A�}�b�v�j
/// </summary>
class SphereMap
{
public:
	HRESULT Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, IDXGISwapChain* inSwap);
	HRESULT InitStaticMesh(LPSTR FileName, SphereMapMesh* pMesh);
	HRESULT InitShader();
	HRESULT MakeTexture();
	HRESULT LoadMaterial(LPSTR FileName, SphereMapMaterial* pMaterial);

	void Render();

private:

	struct ObjVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// �ʒu
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	struct ObjShaderConstantBuffer
	{
		XMMATRIX W;
		XMMATRIX WVP;
		XMFLOAT4 lightDir;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT4 eye;
	};

	HWND hWnd;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;


	// �e�N�X�`��
	SphereMapMesh mesh;
	SphereMapMaterial material;
};

