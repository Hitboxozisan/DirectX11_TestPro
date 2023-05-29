#include "ShaderManager.h"
#include "Singleton.h"
#include "D11Device.h"
#include "ShaderData.h"

using namespace ShaderData;

/// <summary>
/// �R���X�g���N�^
/// </summary>
ShaderManager::ShaderManager()
	:device(Singleton<D11Device>::GetInstance())
{
}

/// <summary>
/// �f�X�g���N�^�@
/// </summary>
ShaderManager::~ShaderManager()
{
}

/// <summary>
/// �V�F�[�_�[�̓ǂݍ��݁E�쐬
/// </summary>
/// <param name="inFileName"></param>
/// <returns></returns>
HRESULT ShaderManager::Load(ObjModelType type)
{

	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;

	// �����R�[�h�ϊ�
	//int length = sizeof(inFileName);
	//wchar_t* wstr = new wchar_t[length];
	//MultiByteToWideChar(CP_ACP, 0, inFileName, -1, wstr, length);
	//LPCWSTR filePath = wstr;
	
	// string����LPCWSTR�ɕϊ�
	int length = MultiByteToWideChar(CP_UTF8, 0, FILE_PATH[type].c_str(), static_cast<int>(FILE_PATH[type].length()), NULL, 0);
	std::wstring wstr(length, 0);
	MultiByteToWideChar(CP_UTF8, 0, FILE_PATH[type].c_str(), static_cast<int>(FILE_PATH[type].length()), &wstr[0], length);
	LPCWSTR filePath = wstr.c_str();
	
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DCompileFromFile(filePath, NULL, NULL, "VS", "vs_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		char* p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		//MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(device.dx11->GetDevice()->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &vertexShader)))
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
	if (FAILED(device.dx11->GetDevice()->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &vertexLayout)))
	{
		return E_FAIL;
	}
	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DCompileFromFile(filePath, NULL, NULL, "PS", "ps_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(device.dx11->GetDevice()->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &pixelShader)))
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

	if (FAILED(device.dx11->GetDevice()->CreateBuffer(&cb, NULL, &constantBuffer)))
	{
		return E_FAIL;
	}

	return S_OK;
}
