static const float pi = 3.1415926f;
static const float two_pi = 6.2831853f;
static const float half_pi = 1.5707963f;
cbuffer cb0 : register(b0) {
	float2 g_window;
}
struct Circle {
	float2 m_pos;	//坐标
	float2 m_r;	//半径,只用[0]
};
static const uint c_circle = 10;
cbuffer cb1 : register(b1) {
	Circle g_circle[c_circle];
}
struct VS {
	float2 m_pos0 : POSITION0;	//原始坐标
	float2 m_width : POSITION1;	//光线宽,只用[0]
	float4 m_color : COLOR0;
};
struct PS {
	float4 m_pos : SV_POSITION;	//渲染坐标
	float4 m_color : COLOR0;	//渲染颜色
	float2 m_pos0 : POSITION0;	//原始坐标
	float2 m_direction : POSITION1;	//光线的反向
};
//着色器
VS vs(VS input) {
	return input;
}
float2 transform(float2 a) {
	float2 v = a;
	v.x /= g_window.x;
	v.y /= g_window.y;
	return v;
}
float vector2_direction(float2 p) {	//S向量2::fg方向r
	return atan2(p.y, p.x);
}
[maxvertexcount(6)]
void gs(line VS input[2], inout TriangleStream<PS> output) {
	//线条展开成四边形
	PS p[4];
	float2 v_direction0 = normalize(input[1].m_pos0 - input[0].m_pos0);	//光的方向
	float v_direction_s = vector2_direction(v_direction0);	//光的方向(标量)
	float v_vertical_s = v_direction_s + half_pi;
	float2 v_vertical = float2(cos(v_vertical_s), sin(v_vertical_s));
	//点坐标
	p[0].m_pos0 = input[0].m_pos0 + v_vertical * input[0].m_width[0];
	p[1].m_pos0 = input[0].m_pos0 - v_vertical * input[0].m_width[0];
	p[2].m_pos0 = input[1].m_pos0 + v_vertical * input[1].m_width[0];
	p[3].m_pos0 = input[1].m_pos0 - v_vertical * input[1].m_width[0];
	//光线方向
	p[0].m_direction = p[2].m_direction = normalize(p[0].m_pos0 - p[2].m_pos0);
	p[1].m_direction = p[3].m_direction = normalize(p[1].m_pos0 - p[3].m_pos0);
	//颜色
	p[0].m_color = p[1].m_color = input[0].m_color;
	p[2].m_color = p[3].m_color = input[1].m_color;
	//渲染坐标
	for (int input = 0; input != 4; ++input) {
		p[input].m_pos = float4(transform(p[input].m_pos0), 0, 1);
	}
	//输出
	output.Append(p[0]);
	output.Append(p[1]);
	output.Append(p[3]);
	output.RestartStrip();

	output.Append(p[0]);
	output.Append(p[2]);
	output.Append(p[3]);
	output.RestartStrip();
}
float2 vector2_rotation(float2 p, float r) {	//S向量2::f旋转r
	float s = sin(r);
	float c = cos(r);
	return float2(p.x * c - p.y * s, p.x * s + p.y * c);
}
float2 vector2_point_position(float2 p0, float2 p1, float r) {	//S向量2::f到点方位r
	float2 v = p1 - p0;
	return vector2_rotation(v, -r);
}
float4 ps(PS input) : SV_TARGET {
	//判断相交
	float v_direction_s = vector2_direction(input.m_direction);
	float v_factor = 1;	//亮度因子
	for (int i = 0; i != c_circle; ++i) {
		//是否过圆坐标
		float2 v_circle_position = vector2_point_position(input.m_pos0, g_circle[i].m_pos, v_direction_s);
		if (abs(v_circle_position.y) <= g_circle[i].m_r.x) {	//光在圆的遮挡半径内
			if (v_circle_position.x >= 0) {
				v_factor *= 0.5f;	//遮挡：光在圆后面
			} else if (length(g_circle[i].m_pos - input.m_pos0) < g_circle[i].m_r.x) {
				v_factor *= 0.5f;	//遮挡：光在圆内
			}
		}
	}
	input.m_color.a *= v_factor;
	return input.m_color;
}