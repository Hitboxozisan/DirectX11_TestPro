#include "TestPolygon.h"
#include "Common.h"
#include "Light.h"

HRESULT TestPolygon::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inContext, Light* inLight)
{
	device = inDevice;
	deviceContext = inContext;
	light = inLight;

	SimplePolygonVertex vertices[] =
	{
		XMFLOAT3(-0.5, -0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// ���_1
		XMFLOAT3(-0.5,  0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// ���_2
		XMFLOAT3( 0.5, -0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// ���_3
		XMFLOAT3( 0.5,  0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// ���_4
	};

	color = { 1.0f, 0.0f, 0.0f, 1.0f };

	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(SimplePolygonVertex) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = vertices;
	if (FAILED(device->CreateBuffer(&bd, &InitData, &vertexBuffer)))
	{
		return E_FAIL;
	}

	// �V�F�[�_�[����������
	if (FAILED(InitShadaer()))
	{
		return E_FAIL;
	}


	return S_OK;
}

void TestPolygon::Fainalize()
{
}

HRESULT TestPolygon::InitShadaer()
{
	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	//�u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	if (FAILED(D3DCompileFromFile(L"Shader/TestPolygon.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0,  &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);

	if (FAILED(device->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &vertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�o�[�e�b�N�X�V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	//���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &vertexLayout)))
	{
		return E_FAIL;
	}
	//�u���u����s�N�Z���V�F�[�_�[�쐬
	if (FAILED(D3DCompileFromFile(L"Shader/TestPolygon.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl�ǂݍ��ݎ��s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pErrors);
	if (FAILED(device->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &pixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0, L"�s�N�Z���V�F�[�_�[�쐬���s", NULL, MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//�R���X�^���g�o�b�t�@�[�쐬�@�����ł͕ϊ��s��n���p
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth = sizeof(SimpleShaderConstantBuffer);
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	cb.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(device->CreateBuffer(&cb, NULL, &constantBuffer)))
	{
		return E_FAIL;
	}
	return S_OK;
}

void TestPolygon::Render(XMVECTOR inEye, XMMATRIX inView, XMMATRIX inProj)
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProj;
	//���[���h�g�����X�t�H�[���i��΍��W�ϊ��j
	mWorld = XMMatrixRotationY(timeGetTime() / 1000.0f);		//�P����yaw��]������
	//�g�p����V�F�[�_�[�̓o�^
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);
	//�V�F�[�_�[�̃R���X�^���g�o�b�t�@�[�Ɋe��f�[�^��n��
	D3D11_MAPPED_SUBRESOURCE pData;
	SimpleShaderConstantBuffer cb;
	if (SUCCEEDED(deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//���[���h�A�J�����A�ˉe�s���n��
		cb.mW = mWorld;
		cb.mW = XMMatrixTranspose(cb.mW);
		XMMATRIX m = mWorld * inView * inProj;
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);

		// �J���[��ω�������
		/*color.x -= 0.001f;
		color.y += 0.001f;
		if (color.x <= 0)
		{
			color.x = 1;
			color.y = 0;
		}
		cb.color = color;*/

		XMVECTOR color = { 0.0f, 1.0f, 0.0f, 1.0f};
		cb.color = color;
		cb.vLightDir = light->GetLight();
		cb.vEye = inEye;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		deviceContext->Unmap(constantBuffer, 0);
	}

	//���̃R���X�^���g�o�b�t�@�[���A�ǂ̃V�F�[�_�[�Ŏg�������w��
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);//�o�[�e�b�N�X�o�b�t�@�[�Ŏg��
	deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);//�s�N�Z���V�F�[�_�[�ł̎g��
	//�o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof(SimplePolygonVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//���_�C���v�b�g���C�A�E�g���Z�b�g
	deviceContext->IASetInputLayout(vertexLayout);
	//�v���~�e�B�u�E�g�|���W�[���Z�b�g
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//�v���~�e�B�u�������_�����O
	deviceContext->Draw(4, 0);
}

