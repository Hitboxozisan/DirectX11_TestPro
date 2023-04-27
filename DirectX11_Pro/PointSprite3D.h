#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// �|�C���g�X�v���C�g��3D��Ԃŕ`�悷��
/// </summary>
class PointSprite3D
{
public:
	PointSprite3D();
	~PointSprite3D();

	HRESULT Init(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext);
	HRESULT InitModel();
	HRESULT MakeShader(LPCWSTR, LPSTR, LPSTR, void**, ID3DBlob**);
	HRESULT MakeTexture();
	void Render();

private:
	//���_�̍\����
	struct PointSprite3DVertex
	{
		XMFLOAT3 Pos; //�ʒu
	};
	//�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�̃A�v�����\���� �������V�F�[�_�[���̃R���X�^���g�o�b�t�@�[�ƈ�v���Ă���K�v����
	struct PointSprite3DBuffer
	{
		XMMATRIX mWVP;
	};

	HWND m_hWnd;
	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	ID3D11InputLayout* m_pVertexLayout;
	ID3D11VertexShader* m_pVertexShader;
	ID3D11GeometryShader* m_pGeometryShader;
	ID3D11PixelShader* m_pPixelShader;
	ID3D11Buffer* m_pConstantBuffer;
	ID3D11Buffer* m_pVertexBuffer;

	// �e�N�X�`���֌W
	ID3D11SamplerState* m_pSampler;			//�e�N�X�`���[�̃T���v���[
	ID3D11ShaderResourceView* m_pTexture;	//�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	ID3D11BlendState* m_pBlendState;

	ID3D11ShaderResourceView* srv = nullptr;
};

