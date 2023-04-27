//グローバル
cbuffer global
{
	matrix g_WVP; //ワールドから射影までの変換行列
};
//構造体
struct GS_INPUT
{
	float4 Pos : SV_POSITION;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
};

//
//
//バーテックスシェーダー
GS_INPUT VS(float4 Pos : POSITION)
{
	GS_INPUT Out;
	Out.Pos = Pos;//ここで頂点を変換しません。なぜならモデル座標のままでジオメトリシェーダーに渡したいからです。
	return Out;
}
//
//
//ジオメトリシェーダー
[maxvertexcount(4)]
void GS_Point(point GS_INPUT Input[1], inout TriangleStream <PS_INPUT> TriStream)
{
	float w = 0;//４つの頂点全てのw値を１番目[0]の頂点のwに合わせる。合わせるのは何番目でもいい　全てが同じなら（ポリゴンにパースがかかってしまうのを防止）

	PS_INPUT p = (PS_INPUT)0;
	p.Pos = mul(Input[0].Pos, g_WVP);
	w = p.Pos.w;
	TriStream.Append(p);

	p.Pos = Input[0].Pos + float4(6, 0, 0, 0);
	p.Pos = mul(p.Pos, g_WVP);
	p.Pos.w = w;
	TriStream.Append(p);

	p.Pos = Input[0].Pos + float4(0, -6, 0, 0);
	p.Pos = mul(p.Pos, g_WVP);
	p.Pos.w = w;
	TriStream.Append(p);

	p.Pos = Input[0].Pos + float4(6, -6, 0, 0);
	p.Pos = mul(p.Pos, g_WVP);
	p.Pos.w = w;
	TriStream.Append(p);

	TriStream.RestartStrip();
}
//
//
//ピクセルシェーダー
float4 PS(PS_INPUT Input) : SV_Target
{
	return float4(1,1,1,1);
}