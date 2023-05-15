#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class KeyManager;

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
	
	const XMMATRIX GetView();
	const XMMATRIX GetProj();
	const XMVECTOR GetCameraPos();
	const XMVECTOR GetLookPos();
	const XMVECTOR GetUpVec();

private:
	// 定数
	const XMVECTOR INITIAL_POS = { 0.0f, 1.0f, 0.0f };
	const XMVECTOR INITIAL_UP_DIR = { 0.0f, 1.0f, 0.0f };

	float yawFlo;
	float zoom;			// ズーム値

	XMFLOAT3 cameraPos;

	XMMATRIX view;
	XMMATRIX proj;
	XMMATRIX yaw;
	XMVECTOR dir;
	XMVECTOR position;
	XMVECTOR lookPos;
	XMVECTOR upDir;

	void MoveCamera();
	void RotateCamera();
	void ZoomInOut();
};

