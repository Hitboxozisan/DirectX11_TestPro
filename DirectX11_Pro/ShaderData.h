#pragma once
#include <unordered_map>
#include <string.h>

// ObjModel�̃t�@�C���p�X�f�[�^
namespace ShaderData
{
	// �e���f���̃t�@�C���p�X
	std::unordered_map<ObjModelType, const std::string> FILE_PATH =
	{
		{ObjModelType::Player, "Shader/Player.hlsl"},
		{ObjModelType::PlayerDir, "Shader/PlayerDir.hlsl"},
		{ObjModelType::TestObj, "Shader/Geometry+Shade+Spec+Texture.hlsl"}
	};
}