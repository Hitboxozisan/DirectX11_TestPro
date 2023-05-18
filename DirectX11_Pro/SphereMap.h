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
/// 環境マッピング（スフィアマップ）
/// </summary>
class SphereMap final
{
public:
	SphereMap();
	~SphereMap();

	HRESULT Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, IDXGISwapChain* inSwap);
	HRESULT InitStaticMesh(LPSTR FileName, SphereMapMesh* pMesh);
	HRESULT InitShader();
	HRESULT MakeTexture();
	HRESULT LoadMaterial(LPSTR FileName, SphereMapMaterial* pMaterial);

	void Render(XMMATRIX player, XMMATRIX view, XMMATRIX proj);

private:

	struct SphereMapVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// 位置
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	struct SphereMapVertex3
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// 位置
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	struct SphereMapConstantBuffer
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

	// テクスチャ
	SphereMapMesh mesh;
	SphereMapMaterial material;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* constantBuffer;
	ID3D11SamplerState* sampleLinear;		// テクスチャーのサンプラー
	ID3D11ShaderResourceView* texture;		// テクスチャー

	TexMetadata info = {};
};

