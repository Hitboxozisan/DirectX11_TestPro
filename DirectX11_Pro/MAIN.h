//ヘッダーファイルのインクルード
#include "Common.h"
#include "Framework.h"
#include "Singleton.h"

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
	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	void Loop();
	void DestroyD3D();

private:

	HWND hWnd;
	
	class D11Device& device;
	class Application* app;

	class SceneManager* sceneManager;
};