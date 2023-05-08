#include "PointSprite3D.h"
#include <locale.h>
#include <memory>
#include "FireSpark.h"


PointSprite3D::PointSprite3D()
{
	// 処理なし
}

PointSprite3D::~PointSprite3D()
{
	// 処理なし
}

HRESULT PointSprite3D::Init(ID3D11Device* inDevice, ID3D11DeviceContext* inDeviceContext)
{
	device = inDevice;
	deviceContext = inDeviceContext;


	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob* pCompiledShader = NULL;
	//バーテックスシェーダー作成
	if (FAILED(MakeShader(L"Shader/PointSprite3D.hlsl", "VS", "vs_5_0", (void**)&vertexShader, &pCompiledShader)))
	{
		return E_FAIL;
	}
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &vertexLayout)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//ジオメトリシェーダー作成
	if (FAILED(MakeShader(L"Shader/PointSprite3D.hlsl", "GS_Point", "gs_5_0", (void**)&geometryShader, &pCompiledShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//ピクセルシェーダー作成
	if (FAILED(MakeShader(L"Shader/PointSprite3D.hlsl", "PS", "ps_5_0", (void**)&pixelShader, &pCompiledShader)))
	{
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);
	//コンスタントバッファー作成　ここでは変換行列渡し用
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

	//点としてのバーテックスバッファー作成
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}

	// テクスチャの作成
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
	// バーテックスバッファー作成
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
	//バーテックスバッファーをセット
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
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	device->CreateSamplerState(&SamDesc, &sampler);

	// マルチバイト文字列からワイド文字列へ変換
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
	
	// リソースとシェーダーリソースビューを作成
	if (FAILED(CreateShaderResourceView(device, image->GetImages(), image->GetImageCount(), info, &texture)))
	{
		// 失敗
		info = {};
		return E_FAIL;
	}

	//アルファブレンド用ブレンドステート作成
	//pngファイル内にアルファ情報がある。アルファにより透過するよう指定している
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
	
	// ビュートランスフォーム
	//XMVECTOR vEyePt = { 0.0f, 1.0f, -2.0f };	//視点位置
	//XMVECTOR vLookatPt = {0.0f, 0.0f, 0.0f};	//注視位置
	//XMVECTOR vUpVec = { 0.0f, 1.0f, 0.0f };		//上方位置
	//View = XMMatrixLookAtLH(vEyePt, vLookatPt, vUpVec);
	//// プロジェクショントランスフォーム
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
	//使用するシェーダーのセット
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->GSSetShader(geometryShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);
	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	PointSprite3DBuffer cb;
	if (SUCCEEDED(deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列を渡す
		XMMATRIX m = wvp;
		m = XMMatrixTranspose(m);
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));
		deviceContext->Unmap(constantBuffer, 0);
	}
	//このコンスタントバッファーをどのシェーダーで使うか
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	deviceContext->GSSetConstantBuffers(0, 1, &constantBuffer);
	deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);

	//頂点インプットレイアウトをセット
	deviceContext->IASetInputLayout(vertexLayout);
	//プリミティブ・トポロジーをセット
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// テクスチャをシェーダーに渡す
	deviceContext->PSSetSamplers(0, 1, &sampler);
	deviceContext->PSSetShaderResources(0, 1, &texture);

	//プリミティブをレンダリング
	deviceContext->Draw(1, 0);

	firespark->Run();
}
