cbuffer cb0 : register(b0) {
	float2 g_window;
}
Texture2D g_texture[4] : register(t0);
SamplerState g_sampler : register(s0);
struct VS {
	float2 pos : POSITION0;
	float2 tex[4] : TEXCOORD;
};
struct PS {
	float4 pos : SV_POSITION;
	float2 tex[4] : TEXCOORD;
};
PS vs(VS input) {
	PS output;
	output.pos = float4(input.pos, 0, 1);
	output.pos.x /= g_window.x;
	output.pos.y /= g_window.y;
	for (int i = 0; i != 4; ++i) {
		output.tex[i] = input.tex[i];
	}
	return output;
}
float4 ps(PS input) : SV_TARGET {
	float4 output = float4(0, 0, 0, 1);
	for (int i = 0; i != 4; ++i) {
		float4 t = g_texture[i].Sample(g_sampler, input.tex[i]);
		output.xyz = lerp(output.xyz, t.xyz, t.w);
	}
	return output;
}