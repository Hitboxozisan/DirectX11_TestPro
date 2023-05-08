#include "PointSprite3D.h"
#include <locale.h>
#include <memory>
#include "FireSpark.h"


PointSprite3D::PointSprite3D()
{
	// �����Ȃ�
}

PointSprite3D::~PointSprite3D()
{
	// �����Ȃ�
}

HRESULT PointSprite3D::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext)
{
	device = inDevice;
	deviceContext = inDeviceContext;


	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob* pCompiledShader = NULL;
	//�o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(MakeShader(L"Shader/PointSprite3D.hlsl", "VS", "vs_5_0", (void**)&vertexShader, &pCompiledShader)))
	{
		return E_FAIL;
	}
	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &vertexLayout)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//�W�I���g���V�F�[�_�[�쐬
	if (FAILED(MakeShader(L"Shader/PointSprite3D.hlsl", "GS_Point", "gs_5_0", (void**)&geometryShader, &pCompiledShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//�s�N�Z���V�F�[�_�[�쐬
	if (FAILED(MakeShader(L"Shader/PointSprite3D.hlsl", "PS", "ps_5_0", (void**)&pixelShader, &pCompiledShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//�R���X�^���g�o�b�t�@�[�쐬�@�����ł͕ϊ��s��n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(PointSprite3DBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(device->CreateBuffer(&cb, NULL, &constantBuffer)))
	{
		return E_FAIL;
	}

	//�_�Ƃ��Ẵo�[�e�b�N�X�o�b�t�@�[�쐬
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}

	// �e�N�X�`���̍쐬
	if (FAILED(MakeTexture()))
	{
		return E_FAIL;
	}

	firespark = new FireSpark();
	firespark->Init(500, XMFLOAT3(0, 0, 0));

	return S_OK;
}

HRESULT PointSprite3D::InitModel()
{
	// �o�[�e�b�N�X�o�b�t�@�[�쐬
	PointSprite3DVertex vertices[] =
	{
		XMFLOAT3(-0.5f, 0.5f, 0.0f),
	};
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(PointSprite3DVertex) * 1;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &vertexBuffer)))
	{
		return E_FAIL;
	}
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(PointSprite3DVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	return S_OK;
}

HRESULT PointSprite3D::MakeShader(LPCWSTR szFileName, LPSTR szFuncName, LPSTR szProfileName, void** ppShader, ID3DBlob** ppBlob)
{
	ID3DBlob* pErrors = NULL;
	if (FAILED(D3DCompileFromFile(szFileName, NULL, NULL, szFuncName, szProfileName, D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION, 0, ppBlob, &pErrors)))
	{
		char* p = (char*)pErrors->GetBufferPointer();
		MessageBoxA(0, p, 0, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	char szProfile[3] = { 0 };
	memcpy(szProfile, szProfileName, 2);
	if (strcmp(szProfile, "vs") == 0)//Vertex Shader
	{
		if (FAILED(device->CreateVertexShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11VertexShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "ps") == 0)//Pixel Shader
	{
		if (FAILED(device->CreatePixelShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11PixelShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "gs") == 0)//Geometry Shader
	{
		if (FAILED(device->CreateGeometryShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11GeometryShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "hs") == 0)//Hull Shader
	{
		if (FAILED(device->CreateHullShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11HullShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "ds") == 0)//Domain Shader
	{
		if (FAILED(device->CreateDomainShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11DomainShader**)ppShader))) return E_FAIL;
	}
	if (strcmp(szProfile, "cs") == 0)//Compute Shader
	{
		if (FAILED(device->CreateComputeShader((*ppBlob)->GetBufferPointer(), (*ppBlob)->GetBufferSize(), NULL, (ID3D11ComputeShader**)ppShader))) return E_FAIL;
	}
	return S_OK;
}

HRESULT PointSprite3D::MakeTexture()
{
	//�e�N�X�`���[�p�T���v���[�쐬
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	device->CreateSamplerState(&SamDesc, &sampler);

	// �}���`�o�C�g�����񂩂烏�C�h������֕ϊ�
	setlocale(LC_CTYPE, "jpn");
	wchar_t filename[256];
	size_t ret;
	mbstowcs_s(&ret, filename, "Data/Image/particle.png", 256);
	auto image = std::make_unique<ScratchImage>();
	HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS_NONE, &info, *image);
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	
	// ���\�[�X�ƃV�F�[�_�[���\�[�X�r���[���쐬
	if (FAILED(CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), info, &texture)))
	{
		// ���s
		info = {};
		return E_FAIL;
	}

	//�A���t�@�u�����h�p�u�����h�X�e�[�g�쐬
	//png�t�@�C�����ɃA���t�@��񂪂���B�A���t�@�ɂ�蓧�߂���悤�w�肵�Ă���
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable = false;
	bd.AlphaToCoverageEnable = false;
	bd.RenderTarget[0].BlendEnable = true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(device->CreateBlendState(&bd, &blendState)))
	{
		return E_FAIL;
	}

	UINT mask = 0xffffffff;
	deviceContext->OMSetBlendState(blendState, NULL, mask);

	return S_OK;
}

void PointSprite3D::Render(XMMATRIX view, XMMATRIX proj)
{
	XMMATRIX World;
	//XMMATRIX View;
	//XMMATRIX Proj;
	
	// �r���[�g�����X�t�H�[��
	//XMVECTOR vEyePt = { 0.0f, 1.0f, -2.0f };	//���_�ʒu
	//XMVECTOR vLookatPt = {0.0f, 0.0f, 0.0f};	//�����ʒu
	//XMVECTOR vUpVec = { 0.0f, 1.0f, 0.0f };		//����ʒu
	//View = XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);
	//// �v���W�F�N�V�����g�����X�t�H�[��
	//Proj = XMMatrixPerspectiveFovLH(XM_PI / 4, (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT, 0.1f, 100.0f);

	for (int i = 0; i < 500; i++)
	{
		XMMATRIX scale, tran;
		scale = XMMatrixScaling(0.01, 0.01, 0.01);
		XMFLOAT3 particlePos = firespark->GetParticlePos(i);
		tran = XMMatrixTranslation(particlePos.x, particlePos.y, particlePos.z);
		World = scale * tran;

		RenderSprite(World * view * proj);
	}

	XMFLOAT3 particlePos = firespark->GetParticlePos(7);
}

void PointSprite3D::RenderSprite(XMMATRIX& wvp)
{
	//�g�p����V�F�[�_�[�̃Z�b�g
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->GSSetShader(geometryShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	PointSprite3DBuffer cb;
	if (SUCCEEDED(deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n��
		XMMATRIX m = wvp;
		m = XMMatrixTranspose(m);
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		deviceContext->Unmap(constantBuffer, 0);
	}
	//���̃R���X�^���g�o�b�t�@�[���ǂ̃V�F�[�_�[�Ŏg����
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	deviceContext->GSSetConstantBuffers(0, 1, &constantBuffer);
	deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);

	//���_�C���v�b�g���C�A�E�g���Z�b�g
	deviceContext->IASetInputLayout(vertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// �e�N�X�`�����V�F�[�_�[�ɓn��
	deviceContext->PSSetSamplers(0, 1, &sampler);
	deviceContext->PSSetShaderResources(0, 1, &texture);

	//�v���~�e�B�u�������_�����O
	deviceContext->Draw(1, 0);

	firespark->Run();
}
