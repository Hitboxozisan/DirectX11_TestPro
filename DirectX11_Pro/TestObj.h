#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;


//struct MyMesh;
// オリジナルメッシュ
struct MyMesh
{
	DWORD dwNumVert = 0;
	DWORD dwNumFace = 0;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;
};

struct MyMaterial
{
	CHAR name[111];
	XMFLOAT4 ka;
	XMFLOAT4 kd;
	XMFLOAT4 ks;
	CHAR textureName[110];
};

class TestObj
{
public:
	TestObj();
	~TestObj();

	HRESULT Init();
	HRESULT InitStaticMesh(LPSTR FileName, MyMesh* pMesh);
	HRESULT	InitShader();
	HRESULT MakeTexture();
	HRESULT LoadMaterial(LPSTR FileName, MyMaterial* pMaterial);

	void Fainalize();
	void Render();

	const XMMATRIX GetPosition() const;

private:

	struct ObjVertex
	{
		XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};		// 位置
		XMFLOAT3 norm = {0.0f, 0.0f, 0.0f};
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

	XMMATRIX position;		// オブジェクトの位置

	class D11Device &device;
	class Camera& camera;
	class MeshManager& meshMgr;
	class ShaderManager& shaderMgr;


	HWND m_hWnd;
	//ComPtr<ID3D11Device> m_pDevice;
	//ID3D11RenderTargetView* m_pBackBuffer_TexRTV;
	//ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;
	//ID3D11Texture2D* m_pBackBuffer_DSTex;

	//↓モデルの種類ごと(モデルの構造が全て同一ならアプリにひとつ）
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Buffer* m_pConstantBuffer;
	//↓モデルごと	
	ID3D11Buffer* m_pVertexBuffer;
	MyMesh m_Mesh;
	MyMaterial m_Material;
	ID3D11SamplerState* m_pSampleLinear;		// テクスチャーのサンプラー
	ID3D11ShaderResourceView* m_pTexture;		// テクスチャー

	TexMetadata info = {};
};

