#pragma once
#include "Common.h"
#include "Framework.h"
#include "SceneManager.h"
#include "D11Device.h"

class SceneBase;
class Text;
class Fps;
class Light;
class TestPolygon;
class PointSprite3D;
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

	ComPtr<IDXGISwapChain> swapChain;

	class D11Device device;

	Text* text;				//文字表示用
	Fps* fps;
	Light* light;			// ライト
	TestPolygon* polygon;
	PointSprite3D* pointSprite;
	class TestObj* testObj;
	Camera* camera;
	SphereMap* skyDome;

};

