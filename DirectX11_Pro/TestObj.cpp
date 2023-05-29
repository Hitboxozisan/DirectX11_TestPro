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
	
	//�V�F�[�_�[������
	//if (FAILED(InitShader()))
	//{
	//	return E_FAIL;
	//}
	//���b�V���쐬
	//if (FAILED(InitStaticMesh("Data/Model/Test/Geometry+Normal+UV.obj", &m_Mesh)))
	//{
	//	return E_FAIL;
	//}
	 
	// �V�F�[�_�[�t�@�C���̓ǂݍ���
	if (FAILED(shaderMgr.Load(ObjModelType::TestObj)))
	{
		MessageBox(0, L"�v���C���[�V�F�[�_�[�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	m_pVertexShader = shaderMgr.GetVertexShader();
	m_pPixelShader = shaderMgr.GetPixelShader();
	m_pVertexLayout = shaderMgr.GetVertexLayout();
	m_pConstantBuffer = shaderMgr.GetConstantBuffer();
	 
	// obj�t�@�C���̓ǂݍ���
	char* file = strdup(FILE_PATH[ObjModelType::TestObj].c_str());
	if (FAILED(meshMgr.LoadMesh(file)))
	{
		MessageBox(0, L"�v���C���[Obj�t�@�C���ǂݍ��ݎ��s", NULL, MB_OK);
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
	DWORD dwVCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwVTCount = 0;//�ǂݍ��݃J�E���^�[
	DWORD dwVNCount = 0;
	DWORD dwFCount = 0;//�ǂݍ��݃J�E���^�[

	char key[200] = { 0 };
	//OBJ�t�@�C�����J���ē��e��ǂݍ���
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");

	//���O�ɒ��_���A�|���S�����𒲂ׂ�
	while (!feof(fp))
	{
		//�L�[���[�h�ǂݍ���
		fscanf_s(fp, "%s ", key, sizeof(key));
		//���_
		if (strcmp(key, "v") == 0)
		{
			pMesh->dwNumVert++;
		}
		// �@��
		if (strcmp(key, "vn") == 0)
		{
			dwVNCount++;
		}
		//�e�N�X�`���[���W
		if (strcmp(key, "vt") == 0)
		{
			dwVTCount++;
		}
		//�t�F�C�X�i�|���S���j
		if (strcmp(key, "f") == 0)
		{
			pMesh->dwNumFace++;
		}
	}

	//�ꎞ�I�ȃ������m�ہi���_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�j
	ObjVertex* pvVertexBuffer = new ObjVertex[pMesh->dwNumFace*3];
	XMFLOAT3* pvCoord = new XMFLOAT3[pMesh->dwNumVert];
	XMFLOAT3* pvNormal = new XMFLOAT3[dwVNCount];
	XMFLOAT2* pvTexture = new XMFLOAT2[dwVTCount];
	int* piFaceBuffer = new int[pMesh->dwNumFace * 3];//�R���_�|���S���Ȃ̂ŁA1�t�F�C�X=3���_(3�C���f�b�N�X)

	//�{�ǂݍ���	
	fseek(fp, SEEK_SET, 0);
	dwVCount = 0;
	dwVTCount = 0;
	dwVNCount = 0;
	dwFCount = 0;

	while (!feof(fp))
	{
		//�L�[���[�h �ǂݍ���
		ZeroMemory(key, sizeof(key));
		fscanf_s(fp, "%s ", key, sizeof(key));

		// �}�e���A���ǂݍ���
		if (strcmp(key, "mtllib") == 0)
		{
			fscanf_s(fp, "%s ", key, sizeof(key));
			LoadMaterial("Data/Material/Geometry+Normal+UV.mtl", &m_Material);
		}
		//���_ �ǂݍ���
		if (strcmp(key, "v") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvCoord[dwVCount].x = -x;//OBJ�͉E����W�n�Ȃ̂�x���邢�͂��𔽓]
			pvCoord[dwVCount].y = y;
			pvCoord[dwVCount].z = z;
			dwVCount++;
		}
		//�@�� �ǂݍ���
		if (strcmp(key, "vn") == 0)
		{
			fscanf_s(fp, "%f %f %f", &x, &y, &z);
			pvNormal[dwVNCount].x = -x;
			pvNormal[dwVNCount].y = y;//OBJ�t�@�C����Y�������t�Ȃ̂ō��킹��
			pvNormal[dwVNCount].z = z;
			dwVNCount++;
		}
		// �e�N�X�`�����W�ǂݍ���
		if (strcmp(key, "vt") == 0)
		{
			fscanf_s(fp, "%f %f", &x, &y);
			pvTexture[dwVTCount].x = x;
			pvTexture[dwVTCount].y = 1 - y;
			dwVTCount++;
		}
		//�t�F�C�X �ǂݍ��݁����_�C���f�b�N�X��
		if (strcmp(key, "f") == 0)
		{
			fscanf_s(fp, "%d/%d/%d %d/%d/%d %d/%d/%d", &v1, &vt1, &vn1, &v2, &vt2, &vn2, &v3, &vt3, &vn3);
			piFaceBuffer[dwFCount * 3] = dwFCount * 3;
			piFaceBuffer[dwFCount * 3 + 1] = dwFCount * 3 + 1;
			piFaceBuffer[dwFCount * 3 + 2] = dwFCount * 3 + 2;
			//���_�\���̂ɑ��
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

	//�o�[�e�b�N�X�o�b�t�@�[���쐬
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

	//�C���f�b�N�X�o�b�t�@�[���쐬
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

	//�ꎞ�I�ȓ��ꕨ�́A���͂�s�v
	delete[] pvCoord;
	delete[] pvTexture;
	delete[] pvNormal;
	delete[] pvVertexBuffer;
	delete[] piFaceBuffer;

	return S_OK;
}

HRESULT TestObj::InitShader()
{
	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DCompileFromFile(L"Shader/Geometry+Shade+Spec+Texture.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		char* p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		//MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(device.dx11->GetDevice()->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pVertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(device.dx11->GetDevice()->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &m_pVertexLayout)))
	{
		return E_FAIL;
	}
	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DCompileFromFile(L"Shader/Geometry+Shade+Spec+Texture.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(device.dx11->GetDevice()->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//�R���X�^���g�o�b�t�@�[�쐬
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
	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	device.dx11->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampleLinear);

	//�t�H���g�̃e�N�X�`���[���쐬
	// �}���`�o�C�g�����񂩂烏�C�h������֕ϊ�
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

	// ���\�[�X�ƃV�F�[�_�[���\�[�X�r���[���쐬
	if (FAILED(CreateShaderResourceView(device.dx11->GetDevice(), image->GetImages(), image->GetImageCount(), info, &m_pTexture)))
	{
		// ���s
		info = {};
		return E_FAIL;
	}

	return S_OK;
}

HRESULT TestObj::LoadMaterial(LPSTR FileName, MyMaterial* pMaterial)
{
	// �}�e���A���t�@�C�����J���ē��e��ǂݍ���
	FILE* fp = NULL;
	fopen_s(&fp, FileName, "rt");

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
			strcpy_s(m_Material.name, key);
		}
		//Ka�@�A���r�G���g
		if (strcmp(key, "Ka") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			m_Material.ka = v;
		}
		//Kd�@�f�B�t���[�Y
		if (strcmp(key, "Kd") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			m_Material.kd = v;
		}
		//Ks�@�X�y�L�����[
		if (strcmp(key, "Ks") == 0)
		{
			fscanf_s(fp, "%f %f %f", &v.x, &v.y, &v.z);
			m_Material.ks = v;
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
			device.dx11->GetDevice()->CreateSamplerState(&SamDesc, &m_pSampleLinear);

			fscanf_s(fp, "%s", &m_Material.textureName, sizeof(m_Material.textureName));
			
			//�e�N�X�`���[�쐬
			// �}���`�o�C�g�����񂩂烏�C�h������֕ϊ�
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
			
			// ���\�[�X�ƃV�F�[�_�[���\�[�X�r���[���쐬
			if (FAILED(CreateShaderResourceView(device.dx11->GetDevice(), image->GetImages(), image->GetImageCount(), info, &m_pTexture)))
			{
				// ���s
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

	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	//position = XMMatrixRotationY(timeGetTime() / 1100.0f);//�P����yaw��]������

	//�g�p����V�F�[�_�[�̓o�^	
	device.dx11->GetDeviceContext()->VSSetShader(m_pVertexShader, NULL, 0);
	device.dx11->GetDeviceContext()->PSSetShader(m_pPixelShader, NULL, 0);
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��	
	D3D11_MAPPED_SUBRESOURCE pData;
	ObjShaderConstantBuffer cb;
	if (SUCCEEDED(device.dx11->GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// ���[���h�s��
		cb.W = position;
		cb.W = XMMatrixTranspose(cb.W);
		//���[���h�A�J�����A�ˉe�s���n��
		XMMATRIX m = position * camera.GetView() * camera.GetProj();
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);
		// ���C�g�̕�����n��
		XMFLOAT3 lightDir = { -1.0f, 0.0f, -1.0f };
		cb.lightDir = XMFLOAT4({lightDir.x, lightDir.y, lightDir.z, 0.0f});
		// �f�B�t���[�Y�J���[��n��
		cb.diffuse = m_Material.kd;
		// �X�y�L�����[���V�F�[�_�[�ɓn��
		cb.specular = m_Material.ks;
		// �J�����ʒu���V�F�[�_�[�ɓn��
		cb.eye = XMFLOAT4(camera.GetPos().x, camera.GetPos().y, camera.GetPos().z, 0.0f);

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ObjShaderConstantBuffer));
		device.dx11->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);
	}
	// �e�N�X�`�����V�F�[�_�[�ɓn��
	device.dx11->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSampleLinear);
	device.dx11->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);
	//���̃R���X�^���g�o�b�t�@�[���g���V�F�[�_�[�̓o�^
	device.dx11->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	device.dx11->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	device.dx11->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	device.dx11->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(ObjVertex);
	UINT offset = 0;
	device.dx11->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh.pVertexBuffer, &stride, &offset);
	//�C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	device.dx11->GetDeviceContext()->IASetIndexBuffer(m_Mesh.pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	//�v���~�e�B�u�������_�����O
	device.dx11->GetDeviceContext()->DrawIndexed(m_Mesh.dwNumFace * 3, 0, 0);
}

const XMMATRIX TestObj::GetPosition() const
{
	return position;
}

