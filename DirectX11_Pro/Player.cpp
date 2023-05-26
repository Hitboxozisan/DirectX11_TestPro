#include "Player.h"
#include "Singleton.h"
#include "MathDx11.h"
#include "D11Device.h"
#include "MaterialManager.h"
#include "MeshManager.h"
#include "Camera.h"
#include "KeyManager.h"


using namespace MathDx11;

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	:device(Singleton<D11Device>::GetInstance())
	,materialMgr(Singleton<Materialmanager>::GetInstance())
	,meshMgr(Singleton<MeshManager>::GetInstance())
	,key(Singleton<KeyManager>::GetInstance())
	,camera(Singleton<Camera>::GetInstance())
	,isAlive(true)
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// 各種終了処理実行
	Fainalize();
}

/// <summary>
/// 初期化処理
/// </summary>
void Player::Init()
{
	param.pos = INITIAL_POS;

	// objファイルの読み込み
	//meshMgr.LoadMesh()
}

/// <summary>
/// 終了処理
/// </summary>
void Player::Fainalize()
{
	
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update()
{
	//Move();
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw()
{
	XMMATRIX position, mTran, mYaw, mPitch, mRoll, mScale;
	position = ConvertXMFLOAT3FromXMMATRIX(param.pos);
	position = XMMatrixRotationY(0.0f);
	mScale = XMMatrixScaling(1.0f, 1.0f, 1.0f);
	mYaw = XMMatrixRotationY(0.0f);
	mPitch = XMMatrixRotationX(0.0f);
	mRoll = XMMatrixRotationZ(0.0f);
	mTran = XMMatrixTranslation(0.0f, 0.0f, 0.0f);

	position = mScale * mYaw * mPitch * mRoll * mTran;

	//ワールドトランスフォーム（絶対座標変換）
	//mWorld = XMMatrixRotationY(timeGetTime() / 1100.0f);//単純にyaw回転させる

	//使用するシェーダーの登録	
	device.dx11->GetDeviceContext()->VSSetShader(vertexShader, NULL, 0);
	device.dx11->GetDeviceContext()->PSSetShader(pixelShader, NULL, 0);
	//シェーダーのコンスタントバッファーに各種データを渡す	
	D3D11_MAPPED_SUBRESOURCE pData;
	ShaderConstantBuffer cb;
	if (SUCCEEDED(device.dx11->GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// ワールド行列
		cb.W = position;
		cb.W = XMMatrixTranspose(cb.W);
		//ワールド、カメラ、射影行列を渡す
		XMMATRIX m = position * camera.GetView() * camera.GetProj();
		cb.WVP = m;
		cb.WVP = XMMatrixTranspose(cb.WVP);
		// ライトの方向を渡す
		XMFLOAT3 lightDir = { -1.0f, 0.0f, -1.0f };
		cb.lightDir = XMFLOAT4({ lightDir.x, lightDir.y, lightDir.z, 0.0f });
		// ディフューズカラーを渡す
		//cb.diffuse = m_Material.kd;
		// スペキュラーをシェーダーに渡す
		//cb.specular = m_Material.ks;
		// カメラ位置をシェーダーに渡す
		cb.eye = XMFLOAT4({ 0.0f, 0.0f, 0.1f, 0.0f });

		memcpy_s(pData.pData, pData.RowPitch, (void*)&cb, sizeof(ShaderConstantBuffer));
		device.dx11->GetDeviceContext()->Unmap(vertexBuffer, 0);
	}
	//// テクスチャをシェーダーに渡す
	//device.dx11->GetDeviceContext()->PSSetSamplers(0, 1, &m_pSampleLinear);
	//device.dx11->GetDeviceContext()->PSSetShaderResources(0, 1, &m_pTexture);
	////このコンスタントバッファーを使うシェーダーの登録
	//device.dx11->GetDeviceContext()->VSSetConstantBuffers(0, 1, &vertexBuffer);
	//device.dx11->GetDeviceContext()->PSSetConstantBuffers(0, 1, &vertexBuffer);
	////頂点インプットレイアウトをセット
	//device.dx11->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	////プリミティブ・トポロジーをセット
	//device.dx11->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	////バーテックスバッファーをセット
	//UINT stride = sizeof(ObjVertex);
	//UINT offset = 0;
	//device.dx11->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_Mesh.pVertexBuffer, &stride, &offset);
	////インデックスバッファーをセット
	//stride = sizeof(int);
	//offset = 0;
	//device.dx11->GetDeviceContext()->IASetIndexBuffer(m_Mesh.pIndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	////プリミティブをレンダリング
	//device.dx11->GetDeviceContext()->DrawIndexed(m_Mesh.dwNumFace * 3, 0, 0);
}

/// <summary>
/// 当たり判定形状
/// </summary>
/// <param name="other"></param>
void Player::OnCollisionEnter(Collision* other)
{
}

/// <summary>
/// 移動処理
/// </summary>
void Player::Move()
{
	// 前方向ベクトルを出す
	XMFLOAT3 Forward = SubXMFLOAT3(param.pos, camera.GetPos());
	// 床にめり込んだりするのを防ぐためY軸は0にする
	Forward.y = 0;

}
