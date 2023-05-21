#pragma once
#include "PlayerBase.h"

using namespace DirectX;

class Player final : public PlayerBase
{
public:
	Player();
	~Player();

	void Init();
	void Fainalize();
	void Update();
	void Draw();

	void OnCollisionEnter(class Collision* other) override;

	const bool IsAlive() { return isAlive; };
private:
	const XMFLOAT3 INITIAL_POS = { 0.0f, 0.0f, 0.0f };

	void Move();

	class KeyManager& key;
	class Camera& camera;

	// ê∂Ç´ÇƒÇ¢ÇÈÇ©
	bool isAlive;
};

