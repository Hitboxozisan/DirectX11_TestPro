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
	//ワールドトランスフォーム
	static float x = -1;
	x += 0.00001;
	XMMATRIX Scale, Tran;
	Scale = XMMatrixScaling(0.01, 0.01, 0.01);
	Tran = XMMatrixTranslation( x, 0, 0);
	World = Scale * Tran;
	// ビュートランスフォーム
	XMVECTOR vEyePt = { 0.0f, 0.0f, -2.0f };	//視点位置
	XMVECTOR vLookatPt = {0.0f, 0.0f, 0.0f};	//注視位置
	XMVECTOR vUpVec = { 0.0f, 1.0f, 0.0f };		//上方位置
	View = XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);
	// プロジェクショントランスフォーム
	&Proj = XMMatrixPerspectiveFovLH(XM_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);
	//使用するシェーダーのセット
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->GSSetShader(m_pGeometryShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	CONSTANT_BUFFER cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列を渡す
		D3DXMATRIX m = World * View * Proj;
		D3DXMatrixTranspose(&m, &m);
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	//このコンスタントバッファーをどのシェーダーで使うか
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->GSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	//プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	//プリミティブをレンダリング
	m_pDeviceContext->Draw(1, 0);
}
