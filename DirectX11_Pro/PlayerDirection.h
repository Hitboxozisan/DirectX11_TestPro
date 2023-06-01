#pragma once

#include "Common.h"
#include "Framework.h"
#include "Collision.h"
#include "CollisionTag.h"

using namespace DirectX;
using namespace Tag;

/// <summary>
/// プレイヤーの向きを示すオブジェクトのクラス
/// プレイヤーの前方に設置
/// </summary>
class PlayerDirection final
{
public:
	PlayerDirection();
	~PlayerDirection();

	HRESULT Init();
	void Update();
	void Draw();

private:
	// プレイヤーのステータス
	struct Param
	{
		XMFLOAT3 pos;
		class Collision* collision;
		CollisionTag tag;
	};

	// メッシュ構造体
	struct PlayerMesh
	{
		DWORD dwNumVert = 0;
		DWORD dwNumFace = 0;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	};

	// マテリアル構造体
	struct PlayerMaterial
	{
		//CHAR name[111];
		XMFLOAT4 ka;
		XMFLOAT4 kd;
		XMFLOAT4 ks;
		//CHAR textureName[110];
	};

	struct ObjVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// 位置
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	const XMFLOAT3 INITIAL_POS = { 0.0f, 0.0f, 0.0f };

	class D11Device& device;
	class MeshManager& meshMgr;
	class ShaderManager& shaderMgr;

	Param param;
	PlayerMesh mesh;
	PlayerMaterial material;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* constantBuffer;
	ID3D11SamplerState* sampleLinear;		// テクスチャのサンプラー
	ID3D11ShaderResourceView* texture;		// テクスチャ
	bool isExist;
};

