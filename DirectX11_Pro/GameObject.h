#pragma once

#include "Common.h"
#include "Framework.h"

using namespace DirectX;

/// <summary>
/// �Q�[���I�u�W�F�N�g�N���X
/// �Q�[����ɑ��݂���I�u�W�F�N�g�͂��̃N���X���p������
/// </summary>
class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	// ���b�V���\����
	struct GameObjectMesh
	{
		DWORD dwNumVert = 0;
		DWORD dwNumFace = 0;
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
	};

	// �}�e���A���\����
	struct GameObjectMaterial
	{
		CHAR name[111];
		XMFLOAT4 ka;
		XMFLOAT4 kd;
		XMFLOAT4 ks;
		CHAR textureName[110];
	};

	HRESULT Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, IDXGISwapChain* inSwap);
	HRESULT InitStaticMesh(LPSTR FileName, GameObjectMesh* pMesh);
	HRESULT InitShader();
	HRESULT LoadMaterial(LPSTR FileName, GameObjectMaterial* pMaterial);

	void Render(XMMATRIX player, XMMATRIX view, XMMATRIX proj);

protected:

	HWND hWnd;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;

private:

};

