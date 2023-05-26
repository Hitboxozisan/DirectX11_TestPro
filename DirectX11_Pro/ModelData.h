#pragma once
#include <unordered_map>
#include <string.h>

#include "ModelTypeData.h"

// ObjModelのファイルパスデータ
namespace ObjModelData
{
	// 各モデルのファイルパス
	std::unordered_map<ObjModelType, const std::string> FILE_PATH =
	{
		{ObjModelType::Player, "Data/Model/Player/Player.obj"}
	};
}