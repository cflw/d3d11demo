cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);
struct VS {
	float3 pos : POSITION0;
	float2 tex : TEXCOORD0;
};
struct PS {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};
PS vs(VS i) {
	PS o;
	o.pos = float4(i.pos, 1);
	o.pos = mul(o.pos, g_world);
	o.pos = mul(o.pos, g_view);
	o.pos = mul(o.pos, g_projection);
	o.tex = i.tex;
	return o;
}
float4 ps(PS i) : SV_TARGET {
	return g_texture.Sample(g_sampler, i.tex);
}