struct PS {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
PS vs(float2 pos : POSITION, float4 color : COLOR0) {
	PS o;
	o.pos = float4(pos, 0, 1);
	o.color = color;
	return o;
}

float4 ps(PS i) : SV_TARGET {
	return i.color;
}