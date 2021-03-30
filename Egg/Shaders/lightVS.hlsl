#include "RootSignatures.hlsli"
#include "cbuffers.hlsli"

struct IAOutput {
	float3 position : POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEXCOORD;
};

struct VSOutput {
	float4 position : SV_Position;
};

[RootSignature(lightRootSig)]
VSOutput main(IAOutput iao) {
	VSOutput vso;
	vso.position =
		mul(
		viewProjMat, mul(
			modelMat, float4(iao.position, 1.0f)
		)
	);
	return vso;
}
