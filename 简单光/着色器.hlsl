cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
cbuffer cb1 : register(b1) {
	float3 g_lightpos;
	float4 g_lightcolor;
	float g_lightstart;
	float g_lightrange;
}
struct VS {
	float3 pos : POSITION0;
	float4 color : COLOR0;
};
struct PS {
	float4 pos0 : SV_POSITION;
	float3 pos1 : POSTION0;
	float4 color : COLOR0;
};
PS vs(VS i) {
	PS o;
	o.pos0 = float4(i.pos, 1);
	o.pos0 = mul(o.pos0, g_world);
	o.pos1 = o.pos0.xyz;
	o.pos0 = mul(o.pos0, g_view);
	o.pos0 = mul(o.pos0, g_projection);
	o.color = i.color;
	return o;
}
float4 ps(PS i) : SV_TARGET {
	float4 color = i.color * g_lightcolor;

	const float d = distance(g_lightpos, i.pos1);
	if (d > g_lightstart) {
		const float s = saturate((d - g_lightstart) / g_lightrange);
		color = lerp(color, float4(0, 0, 0, 1), s);
	}

	return color;
}