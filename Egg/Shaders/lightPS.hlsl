#include "RootSignatures.hlsli"
#include "cbuffers.hlsli"

struct VSOutput {
	float4 position : SV_Position;
};

[RootSignature(lightRootSig)]
float4 main(VSOutput input) : SV_Target
{
	return float4(1,1,1,1);
}
