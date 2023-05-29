#pragma once

#include "Common.h"
#include "Framework.h"
#include "ModelTypeData.h"

using namespace DirectX;

/// <summary>
/// シェーダーの読みこみを行うクラス
/// シングルトン
/// </summary>
class ShaderManager
{
public:
	ShaderManager();
	~ShaderManager();

	HRESULT Load(ObjModelType type);

	ID3D11InputLayout* GetVertexLayout() const { return vertexLayout; }
	ID3D11VertexShader* GetVertexShader() const { return vertexShader; }
	ID3D11PixelShader* GetPixelShader() const { return pixelShader; }
	ID3D11Buffer* GetConstantBuffer() const { return constantBuffer; }

private:

	struct ObjShaderConstantBuffer
	{
		XMMATRIX W;
		XMMATRIX WVP;
		XMFLOAT4 lightDir;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT4 eye;
	};
	
	class D11Device& device;
	ID3D11InputLayout* vertexLayout;
	ID3D11PixelShader* pixelShader;
	ID3D11VertexShader* vertexShader;
	ID3D11Buffer* constantBuffer;

};

