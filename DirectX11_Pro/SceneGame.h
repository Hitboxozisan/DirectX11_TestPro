#pragma once
#include "Common.h"
#include "Framework.h"
#include "SceneManager.h"
#include "D11Device.h"

class SceneBase;
class Fps;
class Light;
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

	ComPtr<ID3D11DeviceContext> deviceContext;
	ComPtr<IDXGISwapChain> swapChain;

	class D11Device& device;
	class Camera& camera;
	class Text& text;					// 文字表示用

	Fps* fps;
	class Light* light;			// ライト
	class TestObj* testObj;
	class Player* player;		// プレイヤー
	SphereMap* skyDome;

};

