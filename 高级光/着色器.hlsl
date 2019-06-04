cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
cbuffer cb1 : register(b1) {
	float4 g_lightdirect;
	float4 g_lightcolor;
}
Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);
struct VS {
	float3 pos : POSITION0;
	float3 norm : NORMAL0;
	float2 tex : TEXCOORD0;
};
struct PS {
	float4 pos : SV_POSITION;
	float3 pos0 : POSITION0;
	float3 norm : NORMAL0;
	float2 tex : TEXCOORD0;
};
PS vs(VS i) {
	PS o;
	o.pos = float4(i.pos, 1);
	o.pos = mul(o.pos, g_world);
	o.pos0 = o.pos;
	o.pos = mul(o.pos, g_view);
	o.pos = mul(o.pos, g_projection);
	o.norm = mul(float4(i.norm, 1), g_world);
	o.tex = i.tex;
	return o;
}
float4 ps(PS i) : SV_TARGET {
	float4 tex = g_texture.Sample(g_sampler, i.tex);
	float4 light = float4(0, 0, 0, 1);
	light += dot(g_lightdirect, float4(-i.norm, 1)) * g_lightcolor;
	light = saturate(light);
	return tex * light;
}
