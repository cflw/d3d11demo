static const float pi = 3.1415926f;
static const float two_pi = 6.2831853f;
cbuffer cb0 : register(b0) {
	matrix g_world;
	matrix g_view;
	matrix g_projection;
}
struct VS {
	float2 pos : POSITION0;
};
struct HS {
	float2 pos : POSITION;
};
struct HS_CONSTANT {
	float EdgeTess[4] : SV_TessFactor;
	float InsideTess[2] : SV_InsideTessFactor;
};
struct DS {
	float2 pos : POSITION;
};
struct PS {
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

HS vs(VS input) {
	return input;
}

static const uint NUM_CONTROL_POINTS = 4;
HS_CONSTANT hs_constant(
	InputPatch<HS, NUM_CONTROL_POINTS> input, 
	uint patchid : SV_PrimitiveID) {
	HS_CONSTANT output;
	output.EdgeTess[0] = 32;
	output.EdgeTess[1] = 32;
	output.EdgeTess[2] = 32;
	output.EdgeTess[3] = 32;
	output.InsideTess[0] = 32;
	output.InsideTess[1] = 32;
	return output;
}

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
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

	float2 v1 = lerp(input[0].pos, input[1].pos, domain.x);
	float2 v2 = lerp(input[2].pos, input[3].pos, domain.x);
	float2 p = lerp(v1, v2, domain.y);

	float z = sin(domain.x * pi * 2) * sin(domain.y * pi * 3) * sin(domain.x * domain.y * pi * 4);
	PS output;
	output.pos = float4(p.x, z, p.y, 1);
	output.pos = mul(output.pos, g_world);
	output.pos = mul(output.pos, g_view);
	output.pos = mul(output.pos, g_projection);

	output.color = float4(domain, 1 - abs(z), 1);

	return output;
}

float4 ps(PS input) : SV_TARGET {
	return input.color;
}