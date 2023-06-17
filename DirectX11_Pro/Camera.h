#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// �J�����N���X
/// </summary>
class Camera final
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();
	void Render(XMFLOAT3 playerPos, float playerYaw);
	void FollowUpPlayer(XMFLOAT3 pos, XMFLOAT3 dir, float yaw);
	
	const XMMATRIX GetView() const { return view; }
	const XMMATRIX GetProj() const { return proj; }
	const XMVECTOR GetPos()const { return position; }
	const XMVECTOR GetLookPos() const { return lookPos; }
	const XMVECTOR GetUpVec() const { return upDir; }

	const XMFLOAT3 GetPos();

	const void SetLookPos(XMVECTOR look) { lookPos = look; }
private:
	// �萔
	const XMVECTOR INITIAL_POS = { 0.0f, 5.0f, -10.0f };
	const XMVECTOR INITIAL_UP_DIR = { 0.0f, 1.0f, 0.0f };

	float yawFlo;
	float pitchFlo;
	float zoom;			// �Y�[���l

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

