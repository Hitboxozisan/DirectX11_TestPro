#include <string.h>
#include <locale.h>
#include "MaterialManager.h"
#include "Singleton.h"
#include "D11Device.h"
#include "DirectXManager.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
MaterialManager::MaterialManager()
	:device(Singleton<D11Device>::GetInstance())
{

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MaterialManager::~MaterialManager()
{

}

/// <summary>
/// �ǂݍ���
/// </summary>
void MaterialManager::Load(LPSTR inFileName, Material* inMaterial)
{
	// �}�e���A���t�@�C�����J���ē��e��ǂݍ���
	FILE* fp = NULL;
	fopen_s(&fp, inFileName, "rt");

	char key[110] = { 0 };
	XMFLOAT4 v(0, 0, 0, 0);
	while (!feof(fp))
	{
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//�}�e���A����
		if (strcmp(key, "newmtl") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			strcpy_s(material.name, key);
		}
		//Ka�@�A���r�G���g
		if (strcmp(key, "Ka") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			material.ka = v;
		}
		//Kd�@�f�B�t���[�Y
		if (strcmp(key, "Kd") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			material.kd = v;
		}
		//Ks�@�X�y�L�����[
		if (strcmp(key, "Ks") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			material.ks = v;
		}
		//map_Kd�@�e�N�X�`���[
		if (strcmp(key, "map_Kd") == 0)
		{
			//�e�N�X�`���[�p�T���v���[�쐬
			D3D11_SAMPLER_DESC SamDesc;
			ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
			SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			device.dx11->GetDevice()->CreateSamplerState(&SamDesc, &sampleLinear);

			fscanf_s(fp, "%s", &material.textureName, sizeof(material.textureName));

			//�e�N�X�`���[�쐬
			// �}���`�o�C�g�����񂩂烏�C�h������֕ϊ�
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

			// ���\�[�X�ƃV�F�[�_�[���\�[�X�r���[���쐬
			if (FAILED(CreateShaderResourceView(device.dx11->GetDevice(), image->GetImages(), image->GetImageCount(), info, &texture)))
			{
				// ���s
				info = {};
				//return E_FAIL;
			}
		}
	}
	fclose(fp);
}
