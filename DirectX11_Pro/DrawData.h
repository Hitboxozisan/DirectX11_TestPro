#pragma once

#include "Common.h"
using namespace DirectX;

struct DrawData
{
	Mesh mesh;
	Material material;
};

// メッシュ構造体
struct Mesh
{
	DWORD dwNumVert = 0;
	DWORD dwNumFace = 0;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};

// マテリアル構造体
struct Material
{
	//CHAR name[111];
	XMFLOAT4 ka;
	XMFLOAT4 kd;
	XMFLOAT4 ks;
	//CHAR textureName[110];
};