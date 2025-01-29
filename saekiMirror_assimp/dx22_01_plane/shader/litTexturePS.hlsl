#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float4 ps_main(in PS_IN input)  : SV_Target
{	
    float4 color;
    
    if(Material.TextureEnable)
    {
            // Sample�֐����e�N�X�`������Y����UV�ʒu�̃s�N�Z���F������ė���
        color = g_Texture.Sample(g_SamplerState, input.tex);
        color *= input.col;
    }
    else
    {
        color = input.col*Material.Diffuse;
    }


    //color = input.col;

    return color;
}

