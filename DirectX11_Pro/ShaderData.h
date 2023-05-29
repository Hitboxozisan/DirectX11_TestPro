#pragma once
#include <unordered_map>
#include <string.h>

#include "ModelTypeData.h"

// ObjModelのファイルパスデータ
namespace ShaderData
{
	// 各モデルのファイルパス
	std::unordered_map<ObjModelType, const std::string> FILE_PATH =
	{
		{ObjModelType::Player, "Shader/Player.hlsl"},
		{ObjModelType::TestObj, "Shader/Geometry+Shade+Spec+Texture.hlsl"}
	};
}