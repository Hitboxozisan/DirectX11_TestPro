#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// カメラクラス
/// </summary>
class Camera final
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();
	void Render();
	void FollowUpPlayer(XMFLOAT3 pos);
	
	const XMMATRIX GetView() const { return view; }
	const XMMATRIX GetProj() const { return proj; }
	const XMVECTOR GetPos()const { return position; }
	const XMVECTOR GetLookPos() const { return lookPos; }
	const XMVECTOR GetUpVec() const { return upDir; }

	const XMFLOAT3 GetPos();

	const void SetLookPos(XMVECTOR look) { lookPos = look; }
private:
	// 定数
	const float ADJUST_POS_Y = 5;
	const float ADJUST_POS_Z = -10;
	const XMVECTOR INITIAL_POS = { 0.0f, 0.0f, 0.0f };
	const XMVECTOR INITIAL_UP_DIR = { 0.0f, 1.0f, 0.0f };

	float yawFlo;
	float pitchFlo;
	float zoom;			// ズーム値

	XMFLOAT3 cameraPos;

	XMMATRIX yaw;
	XMMATRIX pitch;
	XMMATRIX view;
	XMMATRIX proj;
	XMVECTOR dir;
	XMVECTOR position;
	XMVECTOR lookPos;
	XMVECTOR upDir;

	void MoveCamera();
	void RotateCamera();
	void ZoomInOut();

	class KeyManager& key;
	//class Text& text;
};

