cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
cbuffer cb1 : register(b1) {
	float3 g_eyepos;
	float4 g_fogcolor;
	float g_fogstart;
	float g_fogrange;
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
float4 ps(PS i) : SV_TARGET{
	float4 color = i.color;

	const float d = distance(g_eyepos, i.pos1);
	if (d > g_fogstart) {
		const float s = saturate((d - g_fogstart) / g_fogrange);
		color = lerp(color, g_fogcolor, s);
	}

	return color;
}