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

	HRESULT Init();
	HRESULT InitModel();
	HRESULT MakeShader();
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


};

