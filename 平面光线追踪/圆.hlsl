static const float pi = 3.1415926f;
static const float two_pi = 6.2831853f;
cbuffer cb0 : register(b0) {
	float2 g_window;
}
struct VS {
	float2 m_pos : POSITION0;
	float2 m_r : POSITION1;
	float4 m_color : COLOR0;
};
struct PS {
	float4 m_pos : SV_POSITION;
	float4 m_color : COLOR0;
};
VS vs(VS input) {
	return input;
}
float2 transform(float2 a) {
	float2 v = a;
	v.x /= g_window.x;
	v.y /= g_window.y;
	return v;
}
static const int edge_number = 24;
[maxvertexcount(72)]
void gs(point VS input[1], inout TriangleStream<PS> output) {
	float2 center = input[0].m_pos.xy;
	center = transform(center);
	float2 current = float2(cos(0), sin(0));
	current *= input[0].m_r;
	current = transform(current);
	current += center;
	for (int i0 = 1; i0 <= edge_number; ++i0) {
		float direction = (float)i0 / edge_number * two_pi;
		float2 next = float2(cos(direction), sin(direction));
		next *= input[0].m_r;
		next = transform(next);
		next += center;

		PS v;
		v.m_pos = float4(center, 0, 1);
		v.m_color = input[0].m_color;
		output.Append(v);

		v.m_pos = float4(next, 0, 1);
		output.Append(v);
		
		v.m_pos = float4(current, 0, 1);
		output.Append(v);

		output.RestartStrip();
		current = next;
	}
}
float4 ps(PS input) : SV_TARGET {
	return input.m_color;
}