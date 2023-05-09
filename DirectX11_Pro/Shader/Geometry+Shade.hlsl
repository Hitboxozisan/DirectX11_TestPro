//グローバル
cbuffer global
{
	matrix g_mW;//ワールド行列
	matrix g_mWVP; //ワールドから射影までの変換行列
	float4 g_vLightDir; //ライトの方向ベクトル
	float4 g_Diffuse; //拡散反射(色）
};

//バーテックスシェーダー出力構造体
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
};
//
//バーテックスシェーダー
//
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, g_mWVP);
	output.Normal = Normal;

	return output;
}
//
//ピクセルシェーダー
//
float4 PS(VS_OUTPUT Input) : SV_Target
{
	float4 Normal = Input.Normal;
	Normal.w = 0;//w=0で移動成分を反映させない（原理はシェーダーグルが詳しい）
	Normal = mul(Normal,g_mW);
	Normal = normalize(Normal);

	float4 Color = 1.0 * g_Diffuse * dot(Normal,g_vLightDir);//この式はランバートの余弦則

	return Color;
}