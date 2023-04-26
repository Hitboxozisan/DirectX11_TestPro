#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class Light;



/// <summary>
/// テスト用四角形
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

	// 頂点の構造体
	struct SimplePolygonVertex
	{
		XMFLOAT3 pos;			// 位置
		XMFLOAT3 normal;		// 法線、シェーディング（陰影計算）には法線は必須
	};


	struct SimpleShaderConstantBuffer
	{
		XMMATRIX mW;			// ワールド行列
		XMMATRIX WVP;			// ワールドから射影までの変換行列
		XMVECTOR vLightDir;		// ライト方向
		XMVECTOR color;			// ディフーズ色
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

