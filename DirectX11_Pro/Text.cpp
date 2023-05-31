#include <DirectXTex.h>
#include <locale.h>
#include <memory>

#include "Text.h"
#include "Singleton.h"
#include "D11Device.h"

struct ShaderData
{
	LPCSTR vsEntry;
	LPCSTR psEntry;
};

//
//
//
Text::Text()
	:device(Singleton<D11Device>::GetInstance())
{
	// deviceがNULLになるためコメントアウト
	//ZeroMemory(this,sizeof(Text));
	scale=1.0f;
	//カーニング量を個別に設定

	kerning[0]=23;//space
	kerning[1]=16;//!
	kerning[2]=19;//"
	kerning[3]=22;//#
	kerning[4]=22;//$
	kerning[5]=23;//%
	kerning[6]=23;//&
	kerning[7]=18;//'
	kerning[8]=16;//(
	kerning[9]=16;//)
	kerning[10]=18;//*
	kerning[11]=20;//+
	kerning[12]=17;//,
	kerning[13]=17;//-
	kerning[14]=16;//.
	kerning[15]=19;// /
	kerning[16]=20;//0
	kerning[17]=17;//1
	kerning[18]=20;//2
	kerning[19]=21;//3
	kerning[20]=20;//4
	kerning[21]=20;//5
	kerning[22]=20;//6
	kerning[23]=20;//7
	kerning[24]=20;//8
	kerning[25]=20;//9
	kerning[26]=16;//:
	kerning[27]=16;//;
	kerning[28]=18;//<
	kerning[29]=20;//=
	kerning[30]=21;//>
	kerning[31]=19;//?
	kerning[32]=22;//@
	kerning[33]=21;//A
	kerning[34]=20;//B
	kerning[35]=20;//C
	kerning[36]=22;//D
	kerning[37]=18;//E
	kerning[38]=21;//F
	kerning[39]=22;//G
	kerning[40]=22;//H
	kerning[41]=16;//I
	kerning[42]=19;//J
	kerning[43]=21;//K
	kerning[44]=23;//L
	kerning[45]=24;//M
	kerning[46]=21;//N
	kerning[47]=23;//O
	kerning[48]=20;//P
	kerning[49]=22;//Q
	kerning[50]=20;//R
	kerning[51]=19;//S
	kerning[52]=21;//T
	kerning[53]=21;//U
	kerning[54]=24;//V
	kerning[55]=25;//W
	kerning[56]=20;//X
	kerning[57]=20;//Y
	kerning[58]=20;//Z
	kerning[59]=15;//[
	kerning[60]=17;// \/
	kerning[61]=15;//]
	kerning[62]=19;//^
	kerning[63]=21;//_
	kerning[64]=17;//`
	kerning[65]=21;//a
	kerning[66]=21;//b
	kerning[67]=18;//c
	kerning[68]=20;//d
	kerning[69]=19;//e
	kerning[70]=18;//f
	kerning[71]=20;//g
	kerning[72]=18;//h
	kerning[73]=14;//i
	kerning[74]=19;//j
	kerning[75]=21;//k
	kerning[76]=22;//l
	kerning[77]=24;//m
	kerning[78]=20;//n
	kerning[79]=19;//o
	kerning[80]=20;//p
	kerning[81]=19;//q
	kerning[82]=17;//r
	kerning[83]=17;//s
	kerning[84]=19;//t
	kerning[85]=20;//u
	kerning[86]=22;//v
	kerning[87]=22;//w
	kerning[88]=19;//x
	kerning[89]=19;//y
	kerning[90]=19;//z
	kerning[91]=16;//{
	kerning[92]=14;//|
	kerning[93]=18;//}
	kerning[94]=19;//~
	
}
//
//
//
Text::~Text()
{
}
//
//
//
HRESULT Text::Init(DWORD width,DWORD height,float size, XMFLOAT4 vColor)
{
	alpha=vColor.w;
	color=vColor;
	scale=size/25.0f;

	for(int i=0;i<95;i++)
	{
		kerning[i]=22;//固定ピッチにする
		kerning[i]*=scale;		
	}
	//デバイスとコンテキストをコピー
	//device.dx11->GetDeviceContext()deviceContext=pContext;
	//deviceContext->GetDevice(&device);
	//ウィンドウ サイズ
	windowWidth=width;
	windowHeight=height;
	//フォントごとにクアッド作成
	float left=0,top=0,right=0,bottom=0;
	float dimension=DIMENSION/2.0f;
	int cnt=0;
	for(int k=0;k<10;k++)
	{
		for(int i=0;i<10;i++)
		{
			left=k*DIMENSION;
			top=i*DIMENSION+6;
			right=left+(kerning[cnt]+1);
			bottom=top+(DIMENSION*scale-1);
			left/=TEX_DIMENSION;
			top/=TEX_DIMENSION;
			right/=TEX_DIMENSION;
			bottom/=TEX_DIMENSION;
			TextVertex vertices[]=
			{
				XMFLOAT3( 0,DIMENSION*scale,0),XMFLOAT2(left,bottom),//頂点1,
				XMFLOAT3(0,0,0), XMFLOAT2(left,top),//頂点2
				XMFLOAT3( DIMENSION*scale,DIMENSION*scale,0),XMFLOAT2(right,bottom), //頂点3
				XMFLOAT3(  DIMENSION*scale,0,0),XMFLOAT2(right,top), //頂点4
			};
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(TextVertex)*4;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			bd.MiscFlags = 0;

			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;
			if( FAILED(device.dx11->GetDevice()->CreateBuffer(&bd, &InitData, &vertexBuffer[cnt])))
			{
				return E_FAIL;
			}
			cnt++;
		}
	}
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc,sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	device.dx11->GetDevice()->CreateSamplerState(&SamDesc, &sampleLinear);
	//フォントのテクスチャーを作成
	// マルチバイト文字列からワイド文字列へ変換
	setlocale(LC_CTYPE, "jpn");
	wchar_t filename[256];
	size_t ret;
	mbstowcs_s(&ret, filename, "Data/Font/ascii.png", 256);
	auto image = std::make_unique<ScratchImage>();
	HRESULT hr = LoadFromWICFile(filename, WIC_FLAGS_NONE, &info, *image);
	if(FAILED(hr))
	{
		return E_FAIL;
	}
	// リソースとシェーダーリソースビューを作成
	if (FAILED(CreateShaderResourceView(device.dx11->GetDevice(), image->GetImages(), image->GetImageCount(), info, &srv)))
	{
		// 失敗
		info = {};
		return E_FAIL;
	}



	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob *pCompiledShader=NULL;
	ID3DBlob *pErrors=NULL;
	//ブロブからバーテックスシェーダー作成
	if(FAILED(D3DCompileFromFile(L"Shader/Text.hlsl",NULL,NULL,"VS","vs_5_0", 0, 0, &pCompiledShader,&pErrors)))
	{
		MessageBox(0,L"hlsl読み込み失敗",NULL,MB_OK);
		return E_FAIL;
    }
	SAFE_RELEASE(pErrors);
	

	if(FAILED(device.dx11->GetDevice()->CreateVertexShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &vertexShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0,L"バーテックスシェーダー作成失敗",NULL,MB_OK);
		return E_FAIL;
	}
	//頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }, 
	};
	UINT numElements = sizeof(layout)/sizeof(layout[0]);

	//頂点インプットレイアウトを作成
	if( FAILED( device.dx11->GetDevice()->CreateInputLayout(layout, numElements, pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), &vertexLayout)))
		return E_FAIL;
	//ブロブからピクセルシェーダー作成
	if(FAILED(D3DCompileFromFile(L"Shader/Text.hlsl",NULL,NULL,"PS","ps_5_0",0,0,&pCompiledShader,&pErrors)))
	{
		MessageBox(0,L"hlsl読み込み失敗",NULL,MB_OK);
		return E_FAIL;
    }
	SAFE_RELEASE(pErrors);
	if(FAILED(device.dx11->GetDevice()->CreatePixelShader(pCompiledShader->GetBufferPointer(),pCompiledShader->GetBufferSize(),NULL,&pixelShader)))
	{
		SAFE_RELEASE(pCompiledShader);
		MessageBox(0,L"ピクセルシェーダー作成失敗",NULL,MB_OK);
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//コンスタントバッファー作成　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.BindFlags= D3D11_BIND_CONSTANT_BUFFER;
	cb.ByteWidth= sizeof( SIMPLESHADER_CONSTANT_BUFFER );
	cb.CPUAccessFlags=D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags	=0;
	cb.StructureByteStride=0;
	cb.Usage=D3D11_USAGE_DYNAMIC;

	if( FAILED(device.dx11->GetDevice()->CreateBuffer( &cb, NULL, &constantBuffer)))
	{
		return E_FAIL;
	}
	//抜け色設定
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BLEND_DESC));
	bd.IndependentBlendEnable =false;
	bd.AlphaToCoverageEnable=false;
	bd.RenderTarget[0].BlendEnable=true;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	
	if(FAILED(device.dx11->GetDevice()->CreateBlendState(&bd, &blendState)))
	{
		return E_FAIL;
	}

	return S_OK;
}
//
//
//
void Text::Render(char* text,int x,int y)
{
	// ビュートランスフォーム（視点座標変換）
	XMVECTOR vEyePt = { 0.0f, 0.0f, -1.0f };	//カメラ（視点）位置
	XMVECTOR vLookatPt = { 0.0f, 0.0f,  0.0f };	//注視位置
	XMVECTOR vUpVec = { 0.0f, 1.0f,  0.0f };	//上方位置
	view = XMMatrixLookAtLH( vEyePt, vLookatPt, vUpVec );

	// プロジェクショントランスフォーム（射影変換）
	XMMATRIX mOtho = {
		2.0f /(float) ( windowWidth ), 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f /(float) ( windowHeight ), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
		};
	proj = mOtho;

	//トポロジー
	device.dx11->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//頂点インプットレイアウトをセット
	device.dx11->GetDeviceContext()->IASetInputLayout( vertexLayout );

	//使用するシェーダーの登録
	device.dx11->GetDeviceContext()->VSSetShader(vertexShader,NULL,0);
	device.dx11->GetDeviceContext()->PSSetShader(pixelShader,NULL,0);
	//このコンスタントバッファーを使うシェーダーの登録
	device.dx11->GetDeviceContext()->VSSetConstantBuffers(0,1,&constantBuffer );
	device.dx11->GetDeviceContext()->PSSetConstantBuffers(0,1,&constantBuffer );
	//テクスチャーをシェーダーに渡す
	device.dx11->GetDeviceContext()->PSSetSamplers(0,1,&sampleLinear);
	device.dx11->GetDeviceContext()->PSSetShaderResources(0,1, srv.GetAddressOf());
	
	//render
	for(int i=0;i<strlen(text);i++)
	{
		char font=text[i];
		int index=font-32;
		RenderFont(index,x,y);
		x+=kerning[index];
	}
}
//
//
//
void Text::RenderFont(int FontIndex,int x,int y)
{
	//ワールド変換
	XMMATRIX mWorld;
	mWorld = XMMatrixIdentity();
	mWorld = XMMatrixTranslation(x, y, -100);
	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	SIMPLESHADER_CONSTANT_BUFFER cb;
	if( SUCCEEDED(device.dx11->GetDeviceContext()->Map( constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData ) ) )
	{
		//ワールド、カメラ、射影行列を渡す
		XMMATRIX m=mWorld*view*proj;
		m = XMMatrixTranspose(m);
		cb.mWVP=m;
		//カラーを渡す
		cb.vColor=color;
		//透明度を渡す
		cb.fAlpha.x=alpha;

		memcpy_s( pData.pData, pData.RowPitch, (void*)( &cb), sizeof( cb ) );
		device.dx11->GetDeviceContext()->Unmap( constantBuffer, 0 );
	}
	//バーテックスバッファーをセット
	UINT stride = sizeof( TextVertex );
	UINT offset = 0;
	device.dx11->GetDeviceContext()->IASetVertexBuffers( 0, 1, &vertexBuffer[FontIndex], &stride, &offset );

	//抜け色
	UINT ColorKey=0xffffffff;
	device.dx11->GetDeviceContext()->OMSetBlendState(blendState, NULL, ColorKey);
	device.dx11->GetDeviceContext()->Draw( 4, 0 );
}