cbuffer cb0 : register(b0) {
	float2 g_window;
}
Texture2D g_texture[4] : register(t0);
SamplerState g_sampler : register(s0);
struct VS {
	float2 pos : POSITION0;
	float2 tex : TEXCOORD0;
};
struct PS {
	float4 pos : SV_POSITION;
	float2 tex : TEXCOORD0;
};
PS vs(VS i) {
	PS v;
	v.pos = float4(i.pos, 0, 1);
	v.pos.x /= g_window.x;
	v.pos.y /= g_window.y;
	v.tex = i.tex;
	return v;
}
float4 ps(PS i) : SV_TARGET {
	float4 o = float4(0, 0, 0, 1);
	for (int j = 0; j != 4; ++j) {
		float4 t = g_texture[j].Sample(g_sampler, i.tex);
		o.xyz = lerp(o.xyz, t.xyz, t.w);
	}
	return o;
}