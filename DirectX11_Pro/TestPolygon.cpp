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
		XMFLOAT3(-0.5, -0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// 頂点1
		XMFLOAT3(-0.5,  0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// 頂点2
		XMFLOAT3( 0.5, -0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// 頂点3
		XMFLOAT3( 0.5,  0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, -1.0f),	// 頂点4
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

	// シェーダー初期化処理
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
	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob* pErrors = NULL;
	//ブロブからバーテックスシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/TestPolygon.hlsl", NULL, NULL, "VS", "vs_5_0", 0, 0,  &pCompiledShader, &pErrors)))
	{
		MessageBox(0, L"hlsl読み込み失敗", NULL, MB_OK);
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
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL"	, 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトを作成
	if (FAILED(device->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &vertexLayout)))
	{
		return E_FAIL;
	}
	//ブロブからピクセルシェーダー作成
	if (FAILED(D3DCompileFromFile(L"Shader/TestPolygon.hlsl", NULL, NULL, "PS", "ps_5_0", 0, 0, &pCompiledShader, &pErrors)))
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
	//コンスタントバッファー作成　ここでは変換行列渡し用
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
	//ワールドトランスフォーム（絶対座標変換）
	mWorld = XMMatrixRotationY(timeGetTime() / 1000.0f);		//単純にyaw回転させる
	//使用するシェーダーの登録
	deviceContext->VSSetShader(vertexShader, NULL, 0);
	deviceContext->PSSetShader(pixelShader, NULL, 0);
	//シェーダーのコンスタントバッファーに各種データを渡す
	D3D11_MAPPED_SUBRESOURCE pData;
	SimpleShaderConstantBuffer cb;
	if (SUCCEEDED(deviceContext->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド、カメラ、射影行列を渡す
		cb.mW = mWorld;
		cb.mW = XMMatrixTranspose(cb.mW);
		XMMATRIX m = mWorld * inView * inProj;
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);

		// カラーを変化させる
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

	//このコンスタントバッファーを、どのシェーダーで使うかを指定
	deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);//バーテックスバッファーで使う
	deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);//ピクセルシェーダーでの使う
	//バーテックスバッファーをセット
	UINT stride = sizeof(SimplePolygonVertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	//頂点インプットレイアウトをセット
	deviceContext->IASetInputLayout(vertexLayout);
	//プリミティブ・トポロジーをセット
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//プリミティブをレンダリング
	deviceContext->Draw(4, 0);
}

