#pragma once
#include <unordered_map>
#include <string.h>

// ObjModel�̃t�@�C���p�X�f�[�^
namespace ObjModelData
{
	// �e���f���̃t�@�C���p�X
	std::unordered_map<ObjModelType, const std::string> FILE_PATH =
	{
		{ObjModelType::Player, "Data/Model/Player/Player.obj"},
		{ObjModelType::TestObj, "Data/Model/Test/Geometry+Normal+UV.obj"}
	};
}