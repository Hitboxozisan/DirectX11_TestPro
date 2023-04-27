#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// ポイントスプライトを3D空間で描画する
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
	//頂点の構造体
	struct PointSprite3DVertex
	{
		XMFLOAT3 Pos; //位置
	};
	//シェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
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

	// テクスチャ関係
	ID3D11SamplerState* m_pSampler;			//テクスチャーのサンプラー
	ID3D11ShaderResourceView* m_pTexture;	//テクスチャー（用意するのはリソースビューだけでいい）
	ID3D11BlendState* m_pBlendState;

	ID3D11ShaderResourceView* srv = nullptr;
};

