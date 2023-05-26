#include "MeshManager.h"
#include "Singleton.h"

MeshManager::MeshManager()
	:device(Singleton<D11Device>::GetInstance())
{
}

MeshManager::~MeshManager()
{
}

HRESULT MeshManager::LoadMesh(LPSTR fileName)
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
	fopen_s(&fp, fileName, "rt");

	//事前に頂点数、ポリゴン数を調べる
	while (!feof(fp))
	{
		//キーワード読み込み
		fscanf_s(fp, "%s ", key, sizeof(key));
		//頂点
		if (strcmp(key, "v") == 0)
		{
			mesh.dwNumVert++;
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
			mesh.dwNumFace++;
		}
	}

	//一時的なメモリ確保（頂点バッファとインデックスバッファ）
	ObjVertex* pvVertexBuffer = new ObjVertex[mesh.dwNumFace * 3];
	XMFLOAT3* pvCoord = new XMFLOAT3[mesh.dwNumVert];
	XMFLOAT3* pvNormal = new XMFLOAT3[dwVNCount];
	XMFLOAT2* pvTexture = new XMFLOAT2[dwVTCount];
	int* piFaceBuffer = new int[mesh.dwNumFace * 3];//３頂点ポリゴンなので、1フェイス=3頂点(3インデックス)

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
			//LoadMaterial("Data/Material/Geometry+Normal+UV.mtl", &material);
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
	bd.ByteWidth = sizeof(ObjVertex) * mesh.dwNumFace * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = pvVertexBuffer;
	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&bd, &InitData, &mesh.pVertexBuffer)))
	{
		return E_FAIL;
	}

	//インデックスバッファーを作成
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * mesh.dwNumFace * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	InitData.pSysMem = piFaceBuffer;
	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&bd, &InitData, &mesh.pIndexBuffer)))
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

    return E_NOTIMPL;
}
