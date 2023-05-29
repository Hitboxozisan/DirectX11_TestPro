//�O���[�o��
cbuffer global
{
	matrix g_mW;//���[���h�s��
	matrix g_mWVP; //���[���h����ˉe�܂ł̕ϊ��s��
	float4 g_vLightDir; //���C�g�̕����x�N�g��
	float4 g_Diffuse; //�g�U����(�F�j
};

//�o�[�e�b�N�X�V�F�[�_�[�o�͍\����
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Normal : NORMAL;
};
//
//�o�[�e�b�N�X�V�F�[�_�[
//
VS_OUTPUT VS(float4 Pos : POSITION, float4 Normal : NORMAL)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	output.Pos = mul(Pos, g_mWVP);
	output.Normal = Normal;

	return output;
}
//
//�s�N�Z���V�F�[�_�[
//
float4 PS(VS_OUTPUT Input) : SV_Target
{
	float4 Normal = Input.Normal;
	Normal.w = 0;//w=0�ňړ������𔽉f�����Ȃ��i�����̓V�F�[�_�[�O�����ڂ����j
	Normal = mul(Normal,g_mW);
	Normal = normalize(Normal);

	float4 Color = 1.0 * g_Diffuse * dot(Normal,g_vLightDir);//���̎��̓����o�[�g�̗]����

	return Color;
}