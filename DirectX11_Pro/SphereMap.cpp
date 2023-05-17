#include "SphereMap.h"
#include <locale.h>
#include <memory>

/// <summary>
/// コンストラクタ
/// </summary>
SphereMap::SphereMap()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
SphereMap::~SphereMap()
{
	// 処理なし
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name="inDevice"></param>
/// <param name="inContext"></param>
/// <param name="inSwap"></param>
/// <returns></returns>
HRESULT SphereMap::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, IDXGISwapChain* inSwap)
{
	device = inDevice;
	deviceContext = inContext;
	swapChain = inSwap;

	// シェーダー初期化
	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}
	// メッシュ作成
	if (FAILED(InitStaticMesh("Data/Model/ShereMap/SkyDome.obj", &mesh)))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT SphereMap::InitStaticMesh(LPSTR FileName, SphereMapMesh* pMesh)
{
	float x, y, z;
	int v1 = 0, v2 = 0, v3 = 0, v4 = 0;
	int vn1 = 0, vn2 = 0, vn3 = 0, vn4 = 0;
	int vt1 = 0, vt2 = 0, vt3 = 0, vt4 = 0;
	DWORD dwVCount = 0;//読み込みカウンター
	DWORD dwVTCount = 0;//読み込みカウンター
	DWORD dwVNCount = 0;
	DWORD dwFCount = 0;//読み込みカウンター

	char key[200] = { 0 };
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
		// 法線
		if (strcmp(key, "vn") == 0)
		{
			dwVNCount++;
		}
		//テクスチャー座標
		if (strcmp(key, "vt") == 0)
		{
			dwVTCount++;
		}
		//フェイス（ポリゴン）
		if (strcmp(key, "f") == 0)
		{
			pMesh->dwNumFace++;
		}
	}

	//一時的なメモリ確保（頂点バッファとインデックスバッファ）
	SphereMapVertex* pvVertexBuffer = new SphereMapVertex[pMesh->dwNumFace * 4];
	XMFLOAT3* pvCoord = new XMFLOAT3[pMesh->dwNumVert];
	XMFLOAT3* pvNormal = new XMFLOAT3[dwVNCount];
	XMFLOAT2* pvTexture = new XMFLOAT2[dwVTCount];
	int* piFaceBuffer = new int[pMesh->dwNumFace * 4];	//３頂点ポリゴンなので、1フェイス=3頂点(3インデックス)

	//本読み込み	
	fseek(fp, SEEK_SET, 0);
	dwVCount = 0;
	dwVTCount = 0;
	dwVNCount = 0;
	dwFCount = 0;

	while (!feof(fp))
	{
		v1 = 0, v2 = 0, v3 = 0, v4 = 0;
		vn1 = 0, vn2 = 0, vn3 = 0, vn4 = 0;
		vt1 = 0, vt2 = 0, vt3 = 0, vt4 = 0;

		//キーワード 読み込み
		ZeroMemory(key, sizeof(key));
		fscanf_s(fp, "%s ", key, sizeof(key));

		// マテリアル読み込み
		if (strcmp(key, "mtllib") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			LoadMaterial("Data/Material/SkyDome.mtl", &material);
		}
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
			dwVNCount++;
		}
		// テクスチャ座標読み込み
		if (strcmp(key, "vt") == 0)
		{
			fscanf_s(fp, "%f %f", &x, &y);
			pvTexture[dwVTCount].x = x;
			pvTexture[dwVTCount].y = 1 - y;
			dwVTCount++;
		}
		//フェイス 読み込み→頂点インデックスに
		if (strcmp(key, "f") == 0)
		{
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3, &v4, &vt4, &vn4);
			piFaceBuffer[dwFCount * 3] = dwFCount * 3;
			piFaceBuffer[dwFCount * 3 + 1] = dwFCount * 3 + 1;
			piFaceBuffer[dwFCount * 3 + 2] = dwFCount * 3 + 2;
			piFaceBuffer[dwFCount * 3 + 3] = dwFCount * 3 + 3;
			//頂点構造体に代入
			pvVertexBuffer[dwFCount * 3].pos = pvCoord[v1 - 1];
			pvVertexBuffer[dwFCount * 3].norm = pvNormal[vn1 - 1];
			pvVertexBuffer[dwFCount * 3].tex = pvTexture[vt1 - 1];
			pvVertexBuffer[dwFCount * 3 + 1].pos = pvCoord[v2 - 1];
			pvVertexBuffer[dwFCount * 3 + 1].norm = pvNormal[vn2 - 1];
			pvVertexBuffer[dwFCount * 3 + 1].tex = pvTexture[vt2 - 1];
			pvVertexBuffer[dwFCount * 3 + 2].pos = pvCoord[v3 - 1];
			pvVertexBuffer[dwFCount * 3 + 2].norm = pvNormal[vn3 - 1];
			pvVertexBuffer[dwFCount * 3 + 2].tex = pvTexture[vt3 - 1];
			if (v4 != 0 && vt4 != 0 && vn4 != 0)
			{
				pvVertexBuffer[dwFCount * 3 + 3].pos = pvCoord[v4 - 1];
				pvVertexBuffer[dwFCount * 3 + 3].norm = pvNormal[vn4 - 1];
				pvVertexBuffer[dwFCount * 3 + 3].tex = pvTexture[vt4 - 1];
			}
			else
			{
				//pvVertexBuffer[dwFCount * 3 + 3].pos = { 0.0f, 0.0f, 0.0f };
				//pvVertexBuffer[dwFCount * 3 + 3].norm = { 0.0f, 0.0f, 0.0f };
				//pvVertexBuffer[dwFCount * 3 + 3].tex = { 0.0f, 0.0f};
			}
			dwFCount++;
		}
	}

	fclose(fp);

	//バーテックスバッファーを作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SphereMapVertex) * pMesh->dwNumFace * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVertexBuffer;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &pMesh->vertexBuffer)))
	{
		return E_FAIL;
	}

	//インデックスバッファーを作成
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * pMesh->dwNumFace * 4;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = piFaceBuffer;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &pMesh->indexBuffer)))
	{
		return E_FAIL;
	}

	//一時的な入れ物は、もはや不要
	delete[] pvCoord;
	delete[] pvTexture;
	delete[] pvNormal;
	delete[] pvVertexBuffer;
	delete[] piFaceBuffer;

	return S_OK;
}

HRESULT SphereMap::InitShader()
{
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/SphereMap.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		char* p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		//MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(device->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &vertexShader)))
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
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &vertexLayout)))
	{
		return E_FAIL;
	}
	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/SphereMap.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(device->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &pixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"ピクセルシェーダー作成失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//コンスタントバッファー作成
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SphereMapConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(device->CreateBuffer(&cb, NULL, &constantBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}

HRESULT SphereMap::MakeTexture()
{
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	device->CreateSamplerState(&SamDesc, &sampleLinear);

	//フォントのテクスチャーを作成
	// マルチバイト文字列からワイド文字列へ変換
	setlocale(LC_CTYPE, "jpn");
	wchar_t filename[256];
	size_t ret;
	mbstowcs_s(&ret, filename, "Data/Image/BlueSky.bmp", 256);
	auto image = std::make_unique<ScratchImage>();
	HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS_NONE, &info, *image);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// リソースとシェーダーリソースビューを作成
	if (FAILED(CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), info, &texture)))
	{
		// 失敗
		info = {};
		return E_FAIL;
	}

	return S_OK;
}

HRESULT SphereMap::LoadMaterial(LPSTR FileName, SphereMapMaterial* pMaterial)
{
	// マテリアルファイルを開いて内容を読み込む
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");

	char key[110] = { 0 };
	XMFLOAT4 v(0, 0, 0, 0);
	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//マテリアル名
		if (strcmp(key, "newmtl") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			strcpy_s(material.name, key);
		}
		//Ka　アンビエント
		if (strcmp(key, "Ka") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			material.ka = v;
		}
		//Kd　ディフューズ
		if (strcmp(key, "Kd") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			material.kd = v;
		}
		//Ks　スペキュラー
		if (strcmp(key, "Ks") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			material.ks = v;
		}
		//map_Kd　テクスチャー
		if (strcmp(key, "map_Kd") == 0)
		{
			//テクスチャー用サンプラー作成
			D3D11_SAMPLER_DESC SamDesc;
			ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
			SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			device->CreateSamplerState(&SamDesc, &sampleLinear);

			fscanf_s(fp, "%s", &material.textureName, sizeof(material.textureName));

			//テクスチャー作成
			// マルチバイト文字列からワイド文字列へ変換
			setlocale(LC_CTYPE, "jpn");
			wchar_t filename[256];
			size_t ret;
			mbstowcs_s(&ret, filename, material.textureName, 256);
			auto image = std::make_unique<ScratchImage>();
			char name[64];
			wcstombs(name, filename, sizeof(filename));
			char path[64] = "Data/Image/";
			strcat(path, name);
			mbstowcs(filename, path, sizeof(path));
			HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS_NONE, &info, *image);
			if (FAILED(hr))
			{
				return E_FAIL;
			}

			// リソースとシェーダーリソースビューを作成
			if (FAILED(CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), info, &texture)))
			{
				// 失敗
				info = {};
				return E_FAIL;
			}
		}
	}
	fclose(fp);

	return S_OK;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="player"></param>
void SphereMap::Render(XMMATRIX player, XMMATRIX view, XMMATRIX proj)
{
	XMMATRIX mTran, mYaw, mPitch, mRoll, mScale;
	mScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	mYaw = XMMatrixRotationY(0.0f);
	mPitch = XMMatrixRotationX(0.0f);
	mRoll = XMMatrixRotationZ(0.0f);
	mTran = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	//ワールドトランスフォーム（絶対座標変換）
	//mWorld = XMMatrixRotationY(timeGetTime() / 1100.0f);//単純にyaw回転させる

	//使用するシェーダーの登録	
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);
	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	SphereMapConstantBuffer cb;
	if (SUCCEEDED(deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// ワールド行列
		cb.W = player;
		cb.W = XMMatrixTranspose(cb.W);
		//ワールド、カメラ、射影行列を渡す
		XMMATRIX m = player * view * proj;
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);
		// ライトの方向を渡す
		XMFLOAT3 lightDir = { -1.0f, 0.0f, -1.0f };
		cb.lightDir = XMFLOAT4({ lightDir.x, lightDir.y, lightDir.z, 0.0f });
		// ディフューズカラーを渡す
		cb.diffuse = material.kd;
		// スペキュラーをシェーダーに渡す
		cb.specular = material.ks;
		// カメラ位置をシェーダーに渡す
		cb.eye = XMFLOAT4({ 0.0f, 0.0f, 0.1f, 0.0f });

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(SphereMapConstantBuffer));
		deviceContext->Unmap(constantBuffer, 0);
	}
	// テクスチャをシェーダーに渡す
	deviceContext->PSSetSamplers(0, 1, &sampleLinear);
	deviceContext->PSSetShaderResources(0, 1, &texture);
	//このコンスタントバッファーを使うシェーダーの登録
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);
	//頂点インプットレイアウトをセット
	deviceContext->IASetInputLayout(vertexLayout);
	//プリミティブ・トポロジーをセット
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//バーテックスバッファーをセット
	UINT stride = sizeof(SphereMapVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &mesh.vertexBuffer, &stride, &offset);
	//インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	deviceContext->IASetIndexBuffer(mesh.indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//プリミティブをレンダリング
	deviceContext->DrawIndexed(mesh.dwNumFace * 3, 0, 0);

}
