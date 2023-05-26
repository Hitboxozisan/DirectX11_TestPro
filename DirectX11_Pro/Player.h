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
	class Materialmanager& materialMgr;
	class MeshManager& meshMgr;
	class KeyManager& key;
	class Camera& camera;

	ID3D11InputLayout* vertexLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* vertexBuffer;

	// ê∂Ç´ÇƒÇ¢ÇÈÇ©
	bool isAlive;
};

