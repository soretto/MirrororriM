#include "common.hlsl"

PS_IN vs_main(in VS_IN input)
{
    PS_IN output;
	
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

    output.pos = mul(input.pos, wvp);
    output.tex = input.tex;
    output.col = input.col;
	
    output.pos.y -= 0.15;
    output.pos.x += 0.02;
    
    return output;
}

