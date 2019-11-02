cbuffer cb0 : register(b0) {
	float2 g_window;
}
cbuffer cb1 : register(b1) {
	float4 g_color;
}
float4 vs(float2 pos : POSITION) : SV_POSITION {
	float4 v = float4(pos, 0, 1);
	v.x /= g_window.x;
	v.y /= g_window.y;
	return v;
}
float4 ps(float4 pos : SV_POSITION) : SV_TARGET {
	return g_color;
}