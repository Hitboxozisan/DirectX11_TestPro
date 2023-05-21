#pragma once

// Direct3D�̃��C�u�������g�p�ł���悤�ɂ���
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#pragma comment(lib, "winmm.lib")

// Direct3D�̌^�E�N���X�E�֐��Ȃǂ��Ăׂ�悤�ɂ���
#include <d3d11.h>
#include <d3dcompiler.h>

// DirectXMath(���w���C�u����)���g�p�ł���悤�ɂ���
#include <DirectXMath.h>

// DirectX�e�N�X�`�����C�u�������g�p�ł���悤�ɂ���
#include <DirectXTex.h>

// ComPtr���g�p�ł���悤�ɂ���
#include <wrl/client.h>
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// �����DirectX�֌W�̃w�b�_�[���C���N���[�h

//�萔��`
#define WINDOW_WIDTH 1280 //�E�B���h�E��
#define WINDOW_HEIGHT 720 //�E�B���h�E����
#define APP_NAME L"DirectX11_Game"
#define FLAME_RATE 60;
#define ZERO_VECTOR = XMVECTOR{0.0f, 0.0f, 0.0f};
#define ZERO_MATRIX = XMMATRIX{ZERO_VECTOR, ZERO_VECTOR, ZERO_VECTOR, ZERO_VECTOR};

//�}�N��
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}
