static const float pi = 3.1415926f;
static const float two_pi = 6.2831853f;
cbuffer cb0 : register(b0) {
	float2 g_window;
	float g_particlesize;
}
struct VS {
	float2 pos : POSITION;
	float4 color : COLOR0;
};
struct PS {
	float4 pos : SV_POSITION;
	float4 color : COLOR0;
};
PS vs(VS i) {
	PS o;
	o.pos = float4(i.pos, 0, 1);
	o.color = i.color;
	return o;
}
float2 transform(float2 a) {
	float2 v = a;
	v.x /= g_window.x * 0.5f;
	v.y /= g_window.y * 0.5f;
	return v;
}
[maxvertexcount(36)]
void gs(point PS i[1], inout TriangleStream<PS> o) {
	float2 center = i[0].pos.xy;
	center = transform(center);
	float2 current = float2(cos(0), sin(0));
	current *= g_particlesize;
	current = transform(current);
	current += center;
	for (int i0 = 1; i0 <= 12; ++i0) {
		float direction = (float)i0 / 12.f * two_pi;
		float2 next = float2(cos(direction), sin(direction));
		next *= g_particlesize;
		next = transform(next);
		next += center;

		PS v;
		v.pos = float4(center, 0, 1);
		v.color = i[0].color;
		o.Append(v);

		v.pos = float4(next, 0, 1);
		v.color.w = 0;
		o.Append(v);
		
		v.pos = float4(current, 0, 1);
		o.Append(v);

		o.RestartStrip();
		current = next;
	}
}
float4 ps(PS i) : SV_TARGET {
	return i.color;
}