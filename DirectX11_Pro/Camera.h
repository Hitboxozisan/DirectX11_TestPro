#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

class KeyManager;

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
	// íËêî
	const XMVECTOR INITIAL_POS = { 0.0f, 1.0f, 0.0f };
	const XMVECTOR INITIAL_UP_DIR = { 0.0f, 1.0f, 0.0f };

	XMMATRIX view;
	XMMATRIX proj;
	XMVECTOR position;
	XMVECTOR lookPos;
	XMVECTOR upDir;
};

