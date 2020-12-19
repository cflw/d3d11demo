cbuffer cb0 : register(b0) {
	float2 g_window;
}
struct PS {
	float4 pos: SV_POSITION;
	float4 color: COLOR0;
};
PS vs(float2 pos : POSITION, float4 color : COLOR0) {
	PS v;
	v.pos = float4(pos, 0, 1);
	v.pos.x /= g_window.x;
	v.pos.y /= g_window.y;
	v.color = color;
	return v;
}
float4 ps(PS i) : SV_TARGET {
	return i.color;
}