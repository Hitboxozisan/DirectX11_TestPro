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

	struct ShaderConstantBuffer
	{
		XMMATRIX W;
		XMMATRIX WVP;
		XMFLOAT4 lightDir;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;
		XMFLOAT4 eye;
	};

	void Move();

	class D11Device& device;
	class MaterialManager& materialMgr;
	class MeshManager& meshMgr;
	class KeyManager& key;
	class Camera& camera;

	// ê∂Ç´ÇƒÇ¢ÇÈÇ©
	bool isAlive;
};

