#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class FireSpark;

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
	void RenderSprite(XMMATRIX& wvp);

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

	HWND hWnd;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11GeometryShader* geometryShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* vertexBuffer;

	// テクスチャ関係
	ID3D11SamplerState* sampler;			//テクスチャーのサンプラー
	ID3D11ShaderResourceView* texture;	//テクスチャー（用意するのはリソースビューだけでいい）
	ID3D11BlendState* blendState;
	

	TexMetadata info = {};
	// シェーダーリソースビュー
	ID3D11ShaderResourceView* srv = nullptr;

	FireSpark* firespark;
	
};

