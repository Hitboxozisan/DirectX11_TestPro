#include "Common.h"
#include "ObjModel.h"
#include "EnumIterator.h"
#include "ModelTypeData.h"
#include "Singleton.h"
#include "MeshManager.h"

ObjModel::ObjModel()
	:meshMgr(Singleton<MeshManager>::GetInstance())
{
	// 列挙型のイテレータを作成
	typedef EnumIterator<ObjModelType, ObjModelType::Player, ObjModelType::TestObj> mtItr;

	// 全てのモデルのロード
	for (auto itr : mtItr())
	{
		Load(itr);
	}
}

ObjModel::~ObjModel()
{

}

void ObjModel::Init()
{

}

void ObjModel::Update()
{
}

void ObjModel::Draw(const XMFLOAT3& pos, const const ObjModelType mt)
{
}

void ObjModel::Load(const ObjModelType mt)
{
	modelData[mt];

}
