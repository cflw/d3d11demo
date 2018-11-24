cbuffer cb0 : register(b0) {
	float2 g_window;
}
float4 vs_mask(float2 pos : POSITION) : SV_POSITION {
	float4 o = float4(pos, 0, 1);
	o.x /= g_window.x;
	o.y /= g_window.y;
	return o;
}
float4 ps_mask(float4 i : SV_POSITION) : SV_TARGET {
	return float4(1, 1, 1, 1);
}