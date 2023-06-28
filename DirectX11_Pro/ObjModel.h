#pragma once

#include <unordered_map>
#include "DrawData.h"

using namespace DirectX;

enum class ObjModelType;
/// <summary>
/// Objモデルのロードや描画を行うクラス
/// </summary>
class ObjModel
{
public:
	ObjModel();
	~ObjModel();

	void Init();
	void Update();

	void Draw(const XMFLOAT3& pos, const const ObjModelType mt);

private:
	struct ObjVertex
	{
		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };		// 位置
		XMFLOAT3 norm = { 0.0f, 0.0f, 0.0f };
		XMFLOAT2 tex = { 0.0f, 0.0f };
	};

	class MeshManager& meshMgr;

	std::unordered_map<ObjModelType, DrawData> modelData;
	
	void Load(const ObjModelType mt);
};

