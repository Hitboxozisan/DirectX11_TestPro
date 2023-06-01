#pragma once
#include <unordered_map>
#include <string.h>

// ObjModelのファイルパスデータ
namespace ShaderData
{
	// 各モデルのファイルパス
	std::unordered_map<ObjModelType, const std::string> FILE_PATH =
	{
		{ObjModelType::Player, "Shader/Player.hlsl"},
		{ObjModelType::PlayerDir, "Shader/PlayerDir.hlsl"},
		{ObjModelType::TestObj, "Shader/Geometry+Shade+Spec+Texture.hlsl"}
	};
}