#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class Light;



/// <summary>
/// �e�X�g�p�l�p�`
/// </summary>
class TestPolygon
{
public:

	HRESULT Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, Light* inLight);
	void Fainalize();
	HRESULT InitShadaer();
	void Update();
	void Render(XMVECTOR inEye, XMMATRIX inView, XMMATRIX inProj);

private:

	// ���_�̍\����
	struct SimplePolygonVertex
	{
		XMFLOAT3 pos;			// �ʒu
		XMFLOAT3 normal;		// �@���A�V�F�[�f�B���O�i�A�e�v�Z�j�ɂ͖@���͕K�{
	};


	struct SimpleShaderConstantBuffer
	{
		XMMATRIX mW;			// ���[���h�s��
		XMMATRIX WVP;			// ���[���h����ˉe�܂ł̕ϊ��s��
		XMVECTOR vLightDir;		// ���C�g����
		XMVECTOR color;			// �f�B�t�[�Y�F
		XMVECTOR vEye;
	};

	HWND hWnd;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* constantBuffer;

	ID3D11Buffer* vertexBuffer;

	XMFLOAT4 color;
	Light* light;
};

