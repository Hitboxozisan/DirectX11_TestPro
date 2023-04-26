#include "PointSprite3D.h"


PointSprite3D::PointSprite3D()
{
}

PointSprite3D::~PointSprite3D()
{
}

HRESULT PointSprite3D::Init()
{
	return E_NOTIMPL;
}

HRESULT PointSprite3D::InitModel()
{
	return E_NOTIMPL;
}

HRESULT PointSprite3D::MakeShader()
{
	return E_NOTIMPL;
}

void PointSprite3D::Render()
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Proj;
	//���[���h�g�����X�t�H�[��
	static float x = -1;
	x += 0.00001;
	XMMATRIX Scale, Tran;
	Scale = XMMatrixScaling(0.01, 0.01, 0.01);
	Tran = XMMatrixTranslation( x, 0, 0);
	World = Scale * Tran;
	// �r���[�g�����X�t�H�[��
	XMVECTOR vEyePt = { 0.0f, 0.0f, -2.0f };	//���_�ʒu
	XMVECTOR vLookatPt = {0.0f, 0.0f, 0.0f};	//�����ʒu
	XMVECTOR vUpVec = { 0.0f, 1.0f, 0.0f };		//����ʒu
	View = XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);
	// �v���W�F�N�V�����g�����X�t�H�[��
	&Proj = XMMatrixPerspectiveFovLH(XM_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);
	//�g�p����V�F�[�_�[�̃Z�b�g
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->GSSetShader(m_pGeometryShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n��
		D3DXMATRIX m = World * View * Proj;
		D3DXMatrixTranspose(&m, &m);
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//�v���~�e�B�u�������_�����O
	m_pDeviceContext->Draw(1, 0);
}
