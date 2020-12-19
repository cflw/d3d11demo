static const float pi = 3.1415926f;
static const float two_pi = 6.2831853f;
static const float half_pi = 1.5707963f;
cbuffer cb0 : register(b0) {
	float2 g_window;
}
struct Circle {
	float2 m_pos;	//����
	float2 m_r;	//�뾶,ֻ��[0]
};
static const uint c_circle = 10;
cbuffer cb1 : register(b1) {
	Circle g_circle[c_circle];
}
struct VS {
	float2 m_pos0 : POSITION0;	//ԭʼ����
	float2 m_direction : POSITION1;	//���߷���
	float4 m_color : COLOR0;
};
typedef VS HS;
typedef VS DS;
struct HS_CONSTANT {
	float EdgeTess[4] : SV_TessFactor;
	float InsideTess[2] : SV_InsideTessFactor;
};
struct PS {
	float4 m_pos : SV_POSITION;	//��Ⱦ����
	float4 m_color : COLOR0;	//��Ⱦ��ɫ
	float2 m_pos0 : POSITION0;	//ԭʼ����
	float2 m_direction : POSITION1;	//���ߵķ���
};
//��ɫ��
HS vs(VS input) {
	return input;
}
float2 transform(float2 a) {
	float2 v = a;
	v.x /= g_window.x;
	v.y /= g_window.y;
	return v;
}
float vector2_direction(float2 p) {	//S����2::fg����r
	return atan2(p.y, p.x);
}
static const uint NUM_CONTROL_POINTS = 4;
HS_CONSTANT hs_constant(
	InputPatch<HS, NUM_CONTROL_POINTS> input,
	uint patchid : SV_PrimitiveID) {
	HS_CONSTANT output;
	output.EdgeTess[0] = 8;
	output.EdgeTess[1] = 8;
	output.EdgeTess[2] = 8;
	output.EdgeTess[3] = 8;
	output.InsideTess[0] = 8;
	output.InsideTess[1] = 8;
	return output;
}

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(NUM_CONTROL_POINTS)]
[patchconstantfunc("hs_constant")]
DS hs(InputPatch<HS, NUM_CONTROL_POINTS> input,
	uint i : SV_OutputControlPointID,
	uint patchid : SV_PrimitiveID) {

	return input[i];
}

[domain("quad")]
PS ds(HS_CONSTANT constant,
	float2 domain : SV_DomainLocation,
	const OutputPatch<DS, NUM_CONTROL_POINTS> input) {
	//λ��
	float2 p1 = lerp(input[0].m_pos0, input[1].m_pos0, domain.x);
	float2 p2 = lerp(input[2].m_pos0, input[3].m_pos0, domain.x);
	float2 p = lerp(p1, p2, domain.y);
	//����
	float2 d1 = lerp(input[0].m_direction, input[1].m_direction, domain.x);
	float2 d2 = lerp(input[2].m_direction, input[3].m_direction, domain.x);
	float2 d = lerp(d1, d2, domain.y);
	//��ɫ
	float4 c1 = lerp(input[0].m_color, input[1].m_color, domain.x);
	float4 c2 = lerp(input[2].m_color, input[3].m_color, domain.x);
	float4 c = lerp(c1, c2, domain.y);
	//����
	PS output;
	output.m_pos = float4(transform(p), 0, 1);
	output.m_color = c;
	output.m_pos0 = p;
	output.m_direction = -d;
	return output;
}

float2 vector2_rotation(float2 p, float r) {	//S����2::f��תr
	float s = sin(r);
	float c = cos(r);
	return float2(p.x * c - p.y * s, p.x * s + p.y * c);
}
float2 vector2_point_position(float2 p0, float2 p1, float r) {	//S����2::f���㷽λr
	float2 v = p1 - p0;
	return vector2_rotation(v, -r);
}
float4 ps(PS input) : SV_TARGET {
	//�ж��ཻ
	float v_direction_s = vector2_direction(input.m_direction);
	float v_factor = 1;	//��������
	for (int i = 0; i != c_circle; ++i) {
		//�Ƿ��Բ����
		float2 v_circle_position = vector2_point_position(input.m_pos0, g_circle[i].m_pos, v_direction_s);
		if (abs(v_circle_position.y) <= g_circle[i].m_r.x) {	//����Բ���ڵ��뾶��
			if (v_circle_position.x >= 0) {
				v_factor *= 0.5f;	//�ڵ�������Բ����
			} else if (length(g_circle[i].m_pos - input.m_pos0) < g_circle[i].m_r.x) {
				v_factor *= 0.5f;	//�ڵ�������Բ��
			}
		}
	}
	input.m_color.a *= v_factor;
	return input.m_color;
}