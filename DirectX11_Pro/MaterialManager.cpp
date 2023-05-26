#include <string.h>
#include <locale.h>
#include "MaterialManager.h"
#include "Singleton.h"
#include "D11Device.h"
#include "DirectXManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
MaterialManager::MaterialManager()
	:device(Singleton<D11Device>::GetInstance())
{

}

/// <summary>
/// デストラクタ
/// </summary>
MaterialManager::~MaterialManager()
{

}

/// <summary>
/// 読み込み
/// </summary>
void MaterialManager::Load(LPSTR inFileName, Material* inMaterial)
{
	// マテリアルファイルを開いて内容を読み込む
	FILE* fp = NULL;
	fopen_s(&fp, inFileName, "rt");

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
			device.dx11->GetDevice()->CreateSamplerState(&SamDesc, &sampleLinear);

			fscanf_s(fp, "%s", &material.textureName, sizeof(material.textureName));

			//テクスチャー作成
			// マルチバイト文字列からワイド文字列へ変換
			setlocale(LC_CTYPE, "jpn");
			wchar_t filename[256];
			size_t ret;
			mbstowcs_s(&ret, filename, material.textureName, 256);
			auto image = std::make_unique<ScratchImage>();
			HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS_NONE, &info, *image);
			if (FAILED(hr))
			{
				//return E_FAIL;
			}

			// リソースとシェーダーリソースビューを作成
			if (FAILED(CreateShaderResourceView(device.dx11->GetDevice(), image->GetImages(), image->GetImageCount(), info, &texture)))
			{
				// 失敗
				info = {};
				//return E_FAIL;
			}
		}
	}
	fclose(fp);
}
