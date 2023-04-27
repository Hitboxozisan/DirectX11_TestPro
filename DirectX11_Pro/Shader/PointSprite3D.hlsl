//�O���[�o��
cbuffer global
{
	matrix g_WVP; //���[���h����ˉe�܂ł̕ϊ��s��
};
//�\����
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
//�o�[�e�b�N�X�V�F�[�_�[
GS_INPUT VS(float4 Pos : POSITION)
{
	GS_INPUT Out;
	Out.Pos = Pos;//�����Œ��_��ϊ����܂���B�Ȃ��Ȃ烂�f�����W�̂܂܂ŃW�I���g���V�F�[�_�[�ɓn����������ł��B
	return Out;
}
//
//
//�W�I���g���V�F�[�_�[
[maxvertexcount(4)]
void GS_Point(point GS_INPUT Input[1], inout TriangleStream <PS_INPUT> TriStream)
{
	float w = 0;//�S�̒��_�S�Ă�w�l���P�Ԗ�[0]�̒��_��w�ɍ��킹��B���킹��͉̂��Ԗڂł������@�S�Ă������Ȃ�i�|���S���Ƀp�[�X���������Ă��܂��̂�h�~�j

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
//�s�N�Z���V�F�[�_�[
float4 PS(PS_INPUT Input) : SV_Target
{
	return float4(1,1,1,1);
}