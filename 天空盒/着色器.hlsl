cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
TextureCube g_texture : register(t0);
SamplerState g_sampler : register(s0);
struct VS {
	float3 m_pos0 : POSITION0;
};
struct PS {
	float4 m_pos : SV_POSITION;
	float3 m_tex : TEXCOORD0;
};
PS vs(VS i) {
	PS o;
	o.m_pos = float4(i.m_pos0, 1);
	o.m_pos = mul(o.m_pos, g_world);
	o.m_pos = mul(o.m_pos, g_view);
	o.m_pos = mul(o.m_pos, g_projection);
	o.m_pos.z = o.m_pos.w;
	o.m_tex = i.m_pos0;
	return o;
}
float4 ps(PS i) : SV_TARGET{
	return g_texture.Sample(g_sampler, i.m_tex);
}