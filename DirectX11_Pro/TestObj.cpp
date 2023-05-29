#include <locale.h>
#include <memory>
#include "TestObj.h"
#include "Singleton.h"
#include "D11Device.h"
#include "DirectXManager.h"
#include "MathDx11.h"
#include "Camera.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "ModelData.h"
//#include <string.h>

using namespace MathDx11;
using namespace ObjModelData;

TestObj::TestObj()
	:device(Singleton<D11Device>::GetInstance())
	, camera(Singleton<Camera>::GetInstance())
	, meshMgr(Singleton<MeshManager>::GetInstance())
	, shaderMgr(Singleton<ShaderManager>::GetInstance())
{
}

TestObj::~TestObj()
{
}

HRESULT TestObj::Init()
{
	
	//シェーダー初期化
	//if (FAILED(InitShader()))
	//{
	//	return E_FAIL;
	//}
	//メッシュ作成
	//if (FAILED(InitStaticMesh("Data/Model/Test/Geometry+Normal+UV.obj", &m_Mesh)))
	//{
	//	return E_FAIL;
	//}
	 
	// シェーダーファイルの読み込み
	if (FAILED(shaderMgr.Load(ObjModelType::TestObj)))
	{
		MessageBox(0, L"プレイヤーシェーダーファイル読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	m_pVertexShader = shaderMgr.GetVertexShader();
	m_pPixelShader = shaderMgr.GetPixelShader();
	m_pVertexLayout = shaderMgr.GetVertexLayout();
	m_pConstantBuffer = shaderMgr.GetConstantBuffer();
	 
	// objファイルの読み込み
	char* file = strdup(FILE_PATH[ObjModelType::TestObj].c_str());
	if (FAILED(meshMgr.LoadMesh(file)))
	{
		MessageBox(0, L"プレイヤーObjファイル読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	m_Mesh.pVertexBuffer = meshMgr.GetVertexBuffer();
	m_Mesh.pIndexBuffer = meshMgr.GetIndexBuffer();
	m_Material.kd = meshMgr.mateMgr.GetDiffuse();
	m_Material.ks = meshMgr.mateMgr.GetSpecular();
	m_pTexture = meshMgr.mateMgr.GetTexture();
	m_pSampleLinear = meshMgr.mateMgr.GetSmpleLinear();

	
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
	ObjVertex* pvVertexBuffer = new ObjVertex[pMesh->dwNumFace*3];
	XMFLOAT3* pvCoord = new XMFLOAT3[pMesh->dwNumVert];
	XMFLOAT3* pvNormal = new XMFLOAT3[dwVNCount];
	XMFLOAT2* pvTexture = new XMFLOAT2[dwVTCount];
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

		// マテリアル読み込み
		if (strcmp(key, "mtllib") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			LoadMaterial("Data/Material/Geometry+Normal+UV.mtl", &m_Material);
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
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
			piFaceBuffer[dwFCount * 3] = dwFCount * 3;
			piFaceBuffer[dwFCount * 3 + 1] = dwFCount * 3 + 1;
			piFaceBuffer[dwFCount * 3 + 2] = dwFCount * 3 + 2;
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
			dwFCount++;
		}
	}

	fclose(fp);

	//バーテックスバッファーを作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ObjVertex) * pMesh->dwNumFace*3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVertexBuffer;
	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&bd, &InitData, &pMesh->pVertexBuffer)))
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
	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&bd, &InitData, &pMesh->pIndexBuffer)))
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

HRESULT TestObj::InitShader()
{
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/Geometry+Shade+Spec+Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		char* p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		//MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(device.dx11->GetDevice()->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
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
	if (FAILED(device.dx11->GetDevice()->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return E_FAIL;
	}
	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/Geometry+Shade+Spec+Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(device.dx11->GetDevice()->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader)))
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

	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&cb, NULL, &m_pConstantBuffer)))
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
	device.dx11->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampleLinear);

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
	if (FAILED(CreateShaderResourceView(device.dx11->GetDevice(), image->GetImages(), image->GetImageCount(), info, &m_pTexture)))
	{
		// 失敗
		info = {};
		return E_FAIL;
	}

	return S_OK;
}

HRESULT TestObj::LoadMaterial(LPSTR FileName, MyMaterial* pMaterial)
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
			strcpy_s(m_Material.name, key);
		}
		//Ka　アンビエント
		if (strcmp(key, "Ka") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			m_Material.ka = v;
		}
		//Kd　ディフューズ
		if (strcmp(key, "Kd") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			m_Material.kd = v;
		}
		//Ks　スペキュラー
		if (strcmp(key, "Ks") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			m_Material.ks = v;
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
			device.dx11->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampleLinear);

			fscanf_s(fp, "%s", &m_Material.textureName, sizeof(m_Material.textureName));
			
			//テクスチャー作成
			// マルチバイト文字列からワイド文字列へ変換
			setlocale(LC_CTYPE, "jpn");
			wchar_t filename[256];
			size_t ret;
			mbstowcs_s(&ret, filename, m_Material.textureName, 256);
			auto image = std::make_unique<ScratchImage>();
			HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS_NONE, &info, *image);
			if (FAILED(hr))
			{
				return E_FAIL;
			}
			
			// リソースとシェーダーリソースビューを作成
			if (FAILED(CreateShaderResourceView(device.dx11->GetDevice(), image->GetImages(), image->GetImageCount(), info, &m_pTexture)))
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

void TestObj::Fainalize()
{
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pVertexLayout);
	//SAFE_RELEASE(m_pSwapChain);
	//SAFE_RELEASE(m_pBackBuffer_TexRTV);
	//SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	//SAFE_RELEASE(m_pBackBuffer_DSTex);
	//SAFE_RELEASE(m_pDeviceContext);
	//SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pTexture);
}

void TestObj::Render()
{
	XMMATRIX  mTran, mYaw, mPitch, mRoll, mScale;
	position = XMMatrixRotationY(0.0f);
	mScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	mYaw = XMMatrixRotationY(0.0f);
	mPitch = XMMatrixRotationX(0.0f);
	mRoll = XMMatrixRotationZ(0.0f);
	mTran = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	
	position = mScale * mYaw * mPitch * mRoll * mTran;

	//ワールドトランスフォーム（絶対座標変換）
	//position = XMMatrixRotationY(timeGetTime() / 1100.0f);//単純にyaw回転させる

	//使用するシェーダーの登録	
	device.dx11->GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	device.dx11->GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	ObjShaderConstantBuffer cb;
	if (SUCCEEDED(device.dx11->GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// ワールド行列
		cb.W = position;
		cb.W = XMMatrixTranspose(cb.W);
		//ワールド、カメラ、射影行列を渡す
		XMMATRIX m = position * camera.GetView() * camera.GetProj();
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);
		// ライトの方向を渡す
		XMFLOAT3 lightDir = { -1.0f, 0.0f, -1.0f };
		cb.lightDir = XMFLOAT4({lightDir.x, lightDir.y, lightDir.z, 0.0f});
		// ディフューズカラーを渡す
		cb.diffuse = m_Material.kd;
		// スペキュラーをシェーダーに渡す
		cb.specular = m_Material.ks;
		// カメラ位置をシェーダーに渡す
		cb.eye = XMFLOAT4(camera.GetPos().x, camera.GetPos().y, camera.GetPos().z, 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ObjShaderConstantBuffer));
		device.dx11->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);
	}
	// テクスチャをシェーダーに渡す
	device.dx11->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSampleLinear);
	device.dx11->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);
	//このコンスタントバッファーを使うシェーダーの登録
	device.dx11->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	device.dx11->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//頂点インプットレイアウトをセット
	device.dx11->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	//プリミティブ・トポロジーをセット
	device.dx11->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//バーテックスバッファーをセット
	UINT stride = sizeof(ObjVertex);
	UINT offset = 0;
	device.dx11->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh.pVertexBuffer, &stride, &offset);
	//インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	device.dx11->GetDeviceContext()->IASetIndexBuffer(m_Mesh.pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//プリミティブをレンダリング
	device.dx11->GetDeviceContext()->DrawIndexed(m_Mesh.dwNumFace * 3, 0, 0);
}

const XMMATRIX TestObj::GetPosition() const
{
	return position;
}

