#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class FireSpark;

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
	void RenderSprite(XMMATRIX& wvp);

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

	HWND hWnd;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11GeometryShader* geometryShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* vertexBuffer;

	// �e�N�X�`���֌W
	ID3D11SamplerState* sampler;			//�e�N�X�`���[�̃T���v���[
	ID3D11ShaderResourceView* texture;	//�e�N�X�`���[�i�p�ӂ���̂̓��\�[�X�r���[�����ł����j
	ID3D11BlendState* blendState;
	

	TexMetadata info = {};
	// �V�F�[�_�[���\�[�X�r���[
	ID3D11ShaderResourceView* srv = nullptr;

	FireSpark* firespark;
	
};

