//ヘッダーファイルのインクルード
#include "Common.h"
#include "Framework.h"
#include "Singleton.h"

class SceneManager;
class Text;
class Fps;
class Light;
class TestPolygon;
class PointSprite3D;
class TestObj;
class Camera;
class SphereMap;

//
//
//
class MAIN
{
public:
	MAIN();
	~MAIN();

	HRESULT InitWindow(HINSTANCE, INT, INT, INT, INT, LPCWSTR);
	HRESULT Init();
	HRESULT InitD3D();
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	void Loop();
	void Render();
	void DestroyD3D();

private:

	HWND hWnd;
	//ID3D11Device* device;
	//ID3D11DeviceContext* deviceContext;
	//IDXGISwapChain* swapChain;
	//ID3D11RenderTargetView* rtv;
	//ID3D11DepthStencilView* dsv;
	//ID3D11DepthStencilState* depthStencilState;
	//ID3D11Texture2D* ds;

	//MESH* m_pMesh;
	//Text* text;				//文字表示用
	//Fps* fps;
	//Light* light;			// ライト
	//TestPolygon* polygon;
	//PointSprite3D* pointSprite;
	//TestObj* testObj;
	//Camera* camera;
	//SphereMap* skyDome;
	
	class D11Device& device;
	class Application* app;

	SceneManager* sceneManager;

	//class KeyManager& key;
};