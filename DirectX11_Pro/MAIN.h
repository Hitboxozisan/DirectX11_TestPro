//ヘッダーファイルのインクルード
#include "Common.h"
#include "Framework.h"

class Text;
class Fps;
class Light;
class TestPolygon;
class PointSprite3D;

//
//
//
class MAIN
{
public:
	HRESULT InitWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR);
	HRESULT Init();
	HRESULT InitD3D();
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	void Loop();
	void App();
	void Render();
	void DestroyD3D();

	HWND hWnd;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* rtv;
	ID3D11DepthStencilView* dsv;
	ID3D11Texture2D* ds;

	//MESH* m_pMesh;
	Text* text;				//文字表示用
	Fps* fps;
	Light* light;			// ライト
	TestPolygon* polygon;
	PointSprite3D* pointSprite;
};