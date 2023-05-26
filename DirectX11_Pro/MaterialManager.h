#pragma once
#include "Common.h"
#include "Framework.h"

using namespace DirectX;

struct Material
{
	CHAR name[111];
	XMFLOAT4 ka;
	XMFLOAT4 kd;
	XMFLOAT4 ks;
	CHAR textureName[110];
};

/// <summary>
/// マテリアル管理・読み込みクラス
/// </summary>
class MaterialManager
{
public:
	MaterialManager();
	~MaterialManager();

	//struct MyMaterial;

	void Load(LPSTR inFileName, Material* inMaterial);

private:
	class D11Device& device;
	
	Material material;
	ID3D11SamplerState* sampleLinear;
	ID3D11ShaderResourceView* texture;
	TexMetadata info = {};
};

