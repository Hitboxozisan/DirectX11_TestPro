#pragma once

// Direct3Dのライブラリを使用できるようにする
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#pragma comment(lib, "winmm.lib")

// Direct3Dの型・クラス・関数などを呼べるようにする
#include <d3d11.h>
#include <d3dcompiler.h>

// DirectXMath(数学ライブラリ)を使用できるようにする
#include <DirectXMath.h>

// DirectXテクスチャライブラリを使用できるようにする
#include <DirectXTex.h>

// ComPtrを使用できるようにする
#include <wrl/client.h>
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;

// 自作のDirectX関係のヘッダーをインクルード

//定数定義
#define WINDOW_WIDTH 1280 //ウィンドウ幅
#define WINDOW_HEIGHT 720 //ウィンドウ高さ
#define APP_NAME L"DirectX11_Game"
#define FLAME_RATE 60;
#define ZERO_VECTOR = XMVECTOR{0.0f, 0.0f, 0.0f};
#define ZERO_MATRIX = XMMATRIX{ZERO_VECTOR, ZERO_VECTOR, ZERO_VECTOR, ZERO_VECTOR};

//マクロ
#define SAFE_RELEASE(x) if(x){x->Release(); x=NULL;}
