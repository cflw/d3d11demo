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
};

HS vs(VS input) {
	return input;
}

static const uint NUM_CONTROL_POINTS = 4;
HS_CONSTANT hs_constant(
	InputPatch<HS, NUM_CONTROL_POINTS> input, 
	uint patchid : SV_PrimitiveID) {
	HS_CONSTANT output;
	output.EdgeTess[0] = 4;
	output.EdgeTess[1] = 4;
	output.EdgeTess[2] = 4;
	output.EdgeTess[3] = 4;
	output.InsideTess[0] = 4;
	output.InsideTess[1] = 4;
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

	float2 v1 = lerp(input[0].pos, input[1].pos, domain.x);
	float2 v2 = lerp(input[2].pos, input[3].pos, domain.x);
	float2 p = lerp(v1, v2, domain.y);

	PS output;
	output.pos = float4(p, 0, 1);
	return output;
}

float4 ps(PS input) : SV_TARGET {
	return float4(1, 1, 1, 1);
}