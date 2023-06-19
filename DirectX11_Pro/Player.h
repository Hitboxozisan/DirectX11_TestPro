#pragma once
#include "PlayerBase.h"
//#include "ModelData.h"

//using namespace ObjModelData;

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

	void DrawMesh(XMMATRIX pos);
	void Move();
	void Direction();

	class D11Device& device;
	//class MaterialManager& materialMgr;
	class MeshManager& meshMgr;
	class ShaderManager& shaderMgr;
	class KeyManager& key;
	class Camera& camera;

	// �e�X�g------------
	XMMATRIX view;
	XMMATRIX proj;
	XMFLOAT3 eye;

	//-------------------

	// �����Ă��邩
	bool isAlive;
};

