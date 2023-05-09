#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

//struct MyMesh;
// �I���W�i�����b�V��
struct MyMesh
{
	DWORD dwNumVert = 0;
	DWORD dwNumFace = 0;
	ID3D11Buffer* pVertexBuffer;
	ID3D11Buffer* pIndexBuffer;
};

class TestObj
{
public:
	HRESULT Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, IDXGISwapChain* inSwap);
	HRESULT InitStaticMesh(LPSTR FileName, MyMesh* pMesh);
	HRESULT	InitShader();
	HRESULT MakeTexture();

	void Fainalize();
	void Render(XMVECTOR eye, XMVECTOR lookatPt, XMVECTOR upVec);

private:

	struct ObjVertex
	{
		XMFLOAT3 pos = {0.0f, 0.0f, 0.0f};		// �ʒu
		XMFLOAT3 norm = {0.0f, 0.0f, 0.0f};
	};

	struct ObjShaderConstantBuffer
	{
		XMMATRIX W;
		XMMATRIX WVP;
		XMVECTOR lightDir;
		XMVECTOR diffuse;
		XMVECTOR specular;
		XMVECTOR eye;
	};


	HWND m_hWnd;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;
	IDXGISwapChain* m_pSwapChain;

	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;
	ID3D11DepthStencilView* m_pBackBuffer_DSTexDSV;
	ID3D11Texture2D* m_pBackBuffer_DSTex;

	//�����f���̎�ނ���(���f���̍\�����S�ē���Ȃ�A�v���ɂЂƂj
	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Buffer* m_pConstantBuffer;
	//�����f������	
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11ShaderResourceView* srv = nullptr;
	MyMesh m_Mesh;
	//ID3D11SamplerState* m_pSampleLinear;		// �e�N�X�`���[�̃T���v���[
	//ID3D11ShaderResourceView* m_pTexture;		// �e�N�X�`���[

	TexMetadata info = {};
};

