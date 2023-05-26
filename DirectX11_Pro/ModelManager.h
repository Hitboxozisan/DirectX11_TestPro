#pragma once

/// <summary>
/// Objモデルの管理・読み込みクラス
/// シングルトン
/// </summary>
class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	void Init();
	void Load();
	void Draw();
private:

};

