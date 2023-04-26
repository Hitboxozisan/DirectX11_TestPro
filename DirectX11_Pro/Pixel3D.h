#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// 点を3D空間で描画
/// </summary>
class Pixel3D
{
public:
	Pixel3D();
	~Pixel3D();

	HRESULT Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext);
	HRESULT InitModel();
	HRESULT MakeShader(LPCWSTR szFileName, LPSTR szFuncName, LPSTR szProfileName, void** ppShader, ID3DBlob** ppBlob);
	void Render(XMVECTOR inEye, XMMATRIX inView, XMMATRIX inProj);

private:
	//頂点の構造体
	struct Pixel3DVertex
	{
		XMFLOAT3 Pos; //位置
	};

	//Simpleシェーダー用のコンスタントバッファーのアプリ側構造体 もちろんシェーダー内のコンスタントバッファーと一致している必要あり
	struct Pixel3DShaderCnstantBuffer
	{
		XMMATRIX mWVP;
	};

	HWND hWnd;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* constantBuffer;
	ID3D11Buffer* vertexBuffer;
};

