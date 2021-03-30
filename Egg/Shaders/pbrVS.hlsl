#include "RootSignatures.hlsli"
#include "cbBasic.hlsli"
#include "cbuffers.hlsli"

[RootSignature(basicRootSig)]
VSOutput main(IAOutput iao) {
	VSOutput vso;
	//vso.worldPosition = float4(iao.position, 1.0f);
	vso.worldPosition = mul(modelMat, float4(iao.position, 1.0f));
	vso.position = mul(viewProjMat, vso.worldPosition);
	//vso.normal = iao.normal;
	vso.normal = mul(float4(iao.normal, 0.0f), modelMatInv);
	vso.texCoord = iao.texCoord;
	return vso;
}
