cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
struct VS {
	float3 pos : POSITION0;
	float4 color : COLOR0;
};
struct PS {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
PS vs(VS i) {
	PS o;
	o.pos = float4(i.pos, 1);
	o.pos = mul(o.pos, g_world);
	o.pos = mul(o.pos, g_view);
	o.pos = mul(o.pos, g_projection);
	o.color = i.color;
	return o;
}
float4 ps(PS i) : SV_TARGET {
	return i.color;
}