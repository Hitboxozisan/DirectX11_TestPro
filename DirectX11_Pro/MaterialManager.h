#pragma once
#include "Common.h"
#include "Framework.h"
#include "D11Device.h"

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
/// �}�e���A���Ǘ��E�ǂݍ��݃N���X
/// ���b�V���}�l�[�W���ɑ���
/// </summary>
class MaterialManager
{
public:
	MaterialManager();
	~MaterialManager();

	void Load(LPSTR inFileName);

	// �Q�b�^�[
	ID3D11ShaderResourceView* GetTexture() { return texture; }
	ID3D11SamplerState* GetSmpleLinear() { return sampleLinear; }
	XMFLOAT4 GetDiffuse() { return material.kd; }
	XMFLOAT4 GetSpecular() { return material.ks; }

private:
	class D11Device& device;
	
	Material material;
	ID3D11SamplerState* sampleLinear;
	ID3D11ShaderResourceView* texture;
	TexMetadata info = {};
};

