#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;

	//positoin=============================
	// ���[���h�A�r���[�A�v���W�F�N�V�����s����|�����킹�č��W�ϊ����s��
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);
    output.pos = mul(input.pos, wvp);
	
	//color=============================
	//�@���x�N�g���̕ϊ��Ɛ��K�����s��
	float4 normal = float4(input.nrm.xyz, 0.0f);
    float4 worldNormal = mul(normal, World);
	worldNormal = normalize(worldNormal);
	
	//�g�U�����v�Z����
    float d = -dot(Light.Direction.xyz, worldNormal.xyz);
	
    d = saturate(d);
	
    output.col.xyz = input.col.xyz *d* Light.Diffuse.xyz; // �g�U���̉e������Z
    output.col.xyz += input.col.xyz * Light.Ambient.xyz; // �A���r�G���g�������Z
    output.col.xyz += Material.Emission.xyz;
    output.col.a = input.col.a * Material.Diffuse.a; // �A���t�@�l�͂��̂܂܎g�p
	
	//texture=============================
	// �e�N�X�`�����W�͂��̂܂܎g�p
    output.tex = input.tex;
	
    return output;
}

