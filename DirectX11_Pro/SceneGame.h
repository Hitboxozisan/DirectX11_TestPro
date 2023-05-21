#pragma once
#include "SceneManager.h"

class SceneBase;
class Text;
class Fps;
class Light;
class TestPolygon;
class PointSprite3D;
class TestObj;
class Camera;
class SphereMap;

/// <summary>
/// ゲームシーン
/// </summary>
class SceneGame final : public SceneBase
{
public:
	SceneGame(SceneManager* const sceneManager);
	~SceneGame();

	void Initialize() override;	//初期化処理
	void Finalize() override;	//終了処理
	void Activate() override;	//活性化処理
	void Deactivate() override;	//非活性化処理
	void Update() override;		//更新処理
	void Draw() override;		//描画処理

private:

	Text* text;				//文字表示用
	Fps* fps;
	Light* light;			// ライト
	TestPolygon* polygon;
	PointSprite3D* pointSprite;
	TestObj* testObj;
	Camera* camera;
	SphereMap* skyDome;

};

