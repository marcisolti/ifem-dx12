struct IAOutput {
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VSOutput {
	float4 position : SV_Position;
	float4 worldPosition : WORLDPOS;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};