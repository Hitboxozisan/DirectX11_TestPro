#include "TestObj.h"
#include <locale.h>
#include <memory>

HRESULT TestObj::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, IDXGISwapChain* inSwap)
{
	m_pDevice = inDevice;
	m_pDeviceContext = inContext;
	m_pSwapChain = inSwap;

	////バックバッファーテクスチャーを取得（既にあるので作成ではない）
	//ID3D11Texture2D* pBackBuffer_Tex;
	//m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer_Tex);
	////そのテクスチャーに対しレンダーターゲットビュー(RTV)を作成
	//m_pDevice->CreateRenderTargetView(pBackBuffer_Tex, NULL, &m_pBackBuffer_TexRTV);
	//SAFE_RELEASE(pBackBuffer_Tex);

	////デプスステンシルビュー用のテクスチャーを作成
	//D3D11_TEXTURE2D_DESC descDepth;
	//descDepth.Width = WINDOW_WIDTH;
	//descDepth.Height = WINDOW_HEIGHT;
	//descDepth.MipLevels = 1;
	//descDepth.ArraySize = 1;
	//descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	//descDepth.SampleDesc.Count = 1;
	//descDepth.SampleDesc.Quality = 0;
	//descDepth.Usage = D3D11_USAGE_DEFAULT;
	//descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	//descDepth.CPUAccessFlags = 0;
	//descDepth.MiscFlags = 0;
	//m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pBackBuffer_DSTex);
	////そのテクスチャーに対しデプスステンシルビュー(DSV)を作成
	//m_pDevice->CreateDepthStencilView(m_pBackBuffer_DSTex, NULL, &m_pBackBuffer_DSTexDSV);

	////レンダーターゲットビューと深度ステンシルビューをパイプラインにバインド
	//m_pDeviceContext->OMSetRenderTargets(1, &m_pBackBuffer_TexRTV, m_pBackBuffer_DSTexDSV);
	////ビューポートの設定
	//D3D11_VIEWPORT vp;
	//vp.Width = WINDOW_WIDTH;
	//vp.Height = WINDOW_HEIGHT;
	//vp.MinDepth = 0.0f;
	//vp.MaxDepth = 1.0f;
	//vp.TopLeftX = 0;
	//vp.TopLeftY = 0;
	//m_pDeviceContext->RSSetViewports(1, &vp);
	////ラスタライズ設定
	//D3D11_RASTERIZER_DESC rdc;
	//ZeroMemory(&rdc, sizeof(rdc));
	//rdc.CullMode = D3D11_CULL_NONE;
	//rdc.FillMode = D3D11_FILL_SOLID;
	//rdc.FrontCounterClockwise = TRUE;

	//ID3D11RasterizerState* pIr = NULL;
	//m_pDevice->CreateRasterizerState(&rdc, &pIr);
	//m_pDeviceContext->RSSetState(pIr);
	//SAFE_RELEASE(pIr);
	
	//シェーダー初期化
	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}
	//メッシュ作成
	if (FAILED(InitStaticMesh("Data/Model/Test/Geometry+Normal.obj", &m_Mesh)))
	{
		return E_FAIL;
	}

	//テクスチャー作成
	//if (FAILED(MakeTexture()))
	//{
	//	return E_FAIL;
	//}

	return S_OK;
}


HRESULT TestObj::InitStaticMesh(LPSTR FileName, MyMesh* pMesh)
{
	float x, y, z;
	int v1 = 0, v2 = 0, v3 = 0;
	int vn1 = 0, vn2 = 0, vn3 = 0;
	int vt1 = 0, vt2 = 0, vt3 = 0;
	DWORD dwVCount = 0;//読み込みカウンター
	DWORD dwVTCount = 0;//読み込みカウンター
	DWORD dwVNCount = 0;
	DWORD dwFCount = 0;//読み込みカウンター

	char key[190] = { 0 };
	//OBJファイルを開いて内容を読み込む
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");

	//事前に頂点数、ポリゴン数を調べる
	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//頂点
		if (strcmp(key, "v") == 0)
		{
			pMesh->dwNumVert++;
		}
		//テクスチャー座標
		//if (strcmp(key, "vt") == 0)
		//{
		//	dwVTCount++;
		//}
		//フェイス（ポリゴン）
		if (strcmp(key, "f") == 0)
		{
			pMesh->dwNumFace++;
		}
	}

	//一時的なメモリ確保（頂点バッファとインデックスバッファ）
	ObjVertex* pvVertexBuffer = new ObjVertex[pMesh->dwNumVert];
	XMFLOAT3* pvCoord = new XMFLOAT3[pMesh->dwNumVert];
	XMFLOAT3* pvNormal = new XMFLOAT3[pMesh->dwNumVert];
	int* piFaceBuffer = new int[pMesh->dwNumFace * 3];//３頂点ポリゴンなので、1フェイス=3頂点(3インデックス)

	//本読み込み	
	fseek(fp, SEEK_SET, 0);
	dwVCount = 0;
	dwVTCount = 0;
	dwVNCount = 0;
	dwFCount = 0;

	while (!feof(fp))
	{
		//キーワード 読み込み
		ZeroMemory(key, sizeof(key));
		fscanf_s(fp, "%s ", key, sizeof(key));

		//頂点 読み込み
		if (strcmp(key, "v") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvCoord[dwVCount].x = -x;//OBJは右手座標系なのでxあるいはｚを反転
			pvCoord[dwVCount].y = y;
			pvCoord[dwVCount].z = z;
			dwVCount++;
		}
		//法線 読み込み
		if (strcmp(key, "vn") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvNormal[dwVNCount].x = -x;
			pvNormal[dwVNCount].y = y;//OBJファイルはY成分が逆なので合わせる
			pvNormal[dwVNCount].z = z;
			dwVTCount++;
		}
		//フェイス 読み込み→頂点インデックスに
		if (strcmp(key, "f") == 0)
		{
			fscanf_s(fp, "%d//%d %d//%d %d//%d", &v1, &vn1, &v2, &vn2, &v3, &vn3);
			piFaceBuffer[dwFCount * 3] = v1-1;
			piFaceBuffer[dwFCount * 3 + 1] = v2 - 1;
			piFaceBuffer[dwFCount * 3 + 2] = v3 - 1;
			dwFCount++;
			//頂点構造体に代入
			pvVertexBuffer[v1 - 1].pos = pvCoord[v1 - 1];
			pvVertexBuffer[v1 - 1].norm = pvNormal[vn1 - 1];
			pvVertexBuffer[v2 - 1].pos = pvCoord[v2 - 1];
			pvVertexBuffer[v2 - 1].norm = pvNormal[vn2 - 1];
			pvVertexBuffer[v3 - 1].pos = pvCoord[v3 - 1];
			pvVertexBuffer[v3 - 1].norm = pvNormal[vn3 - 1];
		}
	}

	fclose(fp);

	//バーテックスバッファーを作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ObjVertex) * pMesh->dwNumFace;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVertexBuffer;
	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &pMesh->pVertexBuffer)))
	{
		return E_FAIL;
	}

	//インデックスバッファーを作成
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * pMesh->dwNumFace * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = piFaceBuffer;
	if (FAILED(m_pDevice->CreateBuffer(&bd, &InitData, &pMesh->pIndexBuffer)))
	{
		return E_FAIL;
	}

	//一時的な入れ物は、もはや不要
	delete[] pvCoord;
	//delete[] pvTexture;
	delete[] pvNormal;
	delete[] pvVertexBuffer;
	delete[] piFaceBuffer;

	return S_OK;
}

HRESULT TestObj::InitShader()
{
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/Geometry+Shade+Spec.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		char* p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		//MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(m_pDevice->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"バーテックスシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(m_pDevice->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return E_FAIL;
	}
	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/Geometry+Shade+Spec.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//コンスタントバッファー作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(ObjShaderConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT TestObj::MakeTexture()
{
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	//m_pDevice->CreateSamplerState(&SamDesc, &m_pSampleLinear);

	//フォントのテクスチャーを作成
	// マルチバイト文字列からワイド文字列へ変換
	setlocale(LC_CTYPE, "jpn");
	wchar_t filename[256];
	size_t ret;
	mbstowcs_s(&ret, filename, "Data/Image/Test/Hand_ColorMap.bmp", 256);
	auto image = std::make_unique<ScratchImage>();
	HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS_NONE, &info, *image);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// リソースとシェーダーリソースビューを作成
	if (FAILED(CreateShaderResourceView(m_pDevice, image->GetImages(), image->GetImageCount(), info, &srv)))
	{
		// 失敗
		info = {};
		return E_FAIL;
	}

	return S_OK;
}

void TestObj::Fainalize()
{
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pDeviceContext);
	SAFE_RELEASE(m_pDevice);
	//SAFE_RELEASE(m_pSampleLinear);
	//SAFE_RELEASE(m_pTexture);
}

void TestObj::Render(XMMATRIX view, XMMATRIX proj)
{
	XMMATRIX mWorld;
	//XMMATRIX  mView;
	//XMMATRIX  mProj;
	//ワールドトランスフォーム（絶対座標変換）
	mWorld = XMMatrixRotationY(timeGetTime() / 1100.0f);//単純にyaw回転させる
	// ビュートランスフォーム（視点座標変換）
	//XMVECTOR vEyePt = { 0.0f, 0.1f, -0.3f }; //カメラ（視点）位置
	//XMVECTOR vLookatPt = { 0.0f, 0.0f, 0.0f };//注視位置
	//XMVECTOR vUpVec = { 0.0f, 1.0f, 0.0f };//上方位置
	//mView = XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);
	//// プロジェクショントランスフォーム（射影変換）
	//mProj = XMMatrixPerspectiveFovLH(XM_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 110.0f);

	//使用するシェーダーの登録	
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	ObjShaderConstantBuffer cb;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// ワールド行列
		cb.W = mWorld;
		cb.W = XMMatrixTranspose(cb.W);
		//ワールド、カメラ、射影行列を渡す
		XMMATRIX m = mWorld * view * proj;
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);
		// ライトの方向を渡す
		XMFLOAT3 lightDir = { 1.0f, 1.0f, -1.0f };
		cb.lightDir = XMVECTOR({lightDir.x, lightDir.y, lightDir.z, 0.0f});
		// ディフューズカラーを渡す
		cb.diffuse = XMVECTOR({ 0.5, 0.5, 0.5, 1.0 });
		// スペキュラーをシェーダーに渡す
		cb.specular = XMVECTOR({ 1.0f, 1.0f, 1.0f, 1.0f });
		// カメラ位置をシェーダーに渡す
		cb.eye = XMVECTOR({ 0.0f, 0.1f, -0.3f, 1.0f});

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ObjShaderConstantBuffer));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}
	// テクスチャをシェーダーに渡す
	//m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear);
	//m_pDeviceContext->PSSetShaderResources(0, 1, &srv);
	//このコンスタントバッファーを使うシェーダーの登録
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	//プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//バーテックスバッファーをセット
	UINT stride = sizeof(ObjVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_Mesh.pVertexBuffer, &stride, &offset);
	//インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	m_pDeviceContext->IASetIndexBuffer(m_Mesh.pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//プリミティブをレンダリング
	m_pDeviceContext->DrawIndexed(m_Mesh.dwNumFace * 3, 0, 0);
}
