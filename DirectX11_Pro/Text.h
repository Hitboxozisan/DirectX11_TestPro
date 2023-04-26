#pragma once

#include <windows.h>
#include <d3d11.h>
#include <d3dCompiler.h>

#include <DirectXMath.h>

#include <wrl/client.h>
#include <DirectXTex.h>
using Microsoft::WRL::ComPtr;
using namespace DirectX;

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "dxgi.lib")


#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}
#define DIMENSION 25.0f
#define TEX_DIMENSION 256.0f

//
//
struct SIMPLESHADER_CONSTANT_BUFFER
{
	XMMATRIX mWVP;
	XMFLOAT4 vColor;
	XMFLOAT4 fAlpha;
};
//
//
struct TextVertex
{
	XMFLOAT3 Pos; //位置
	XMFLOAT2 vTex; //テクスチャー座標
};
//
//
class Text
{
public:
	Text();
	~Text();

	HRESULT Init(ID3D11DeviceContext* pContext, DWORD width, DWORD height, float size, XMFLOAT4 vColor);
	void Render(char* text, int x, int y);
	void RenderFont(int FontIndex, int x, int y);

	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	ID3D11SamplerState* sampleLinear;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* vertexLayout;
	ID3D11Buffer* constantBuffer;
	ID3D11BlendState* blendState;


	DWORD windowWidth;
	DWORD windowHeight;
	ID3D11ShaderResourceView* asciiTexture;
	ID3D11Buffer* vertexBuffer[100];
	XMMATRIX view;
	XMMATRIX proj;
	float kerning[100];
	float scale;//25pixelを基準 25pixel=1.0f
	float alpha;
	XMFLOAT4 color;

	TexMetadata info = {};
	// シェーダーリソースビュー（画像データ読み取りハンドル）
	ComPtr<ID3D11ShaderResourceView> srv = nullptr;
};