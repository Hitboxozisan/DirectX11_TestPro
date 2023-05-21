#pragma once
#include "SceneManager.h"

class SceneBase;

/// <summary>
/// タイトル画面
/// </summary>
class SceneTitle final : public SceneBase
{
public:
	SceneTitle(SceneManager* const sceneManager);
	~SceneTitle();

	void Initialize() override;	//初期化処理
	void Finalize() override;	//終了処理
	void Activate() override;	//活性化処理
	void Deactivate() override;	//非活性化処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

private:


};

