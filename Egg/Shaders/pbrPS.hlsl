// Physically Based Shading <3
// Ctrl-C + Ctrl-V from here:
// https://seblagarde.files.wordpress.com/2015/07/course_notes_moving_frostbite_to_pbr_v32.pdf

#include "cbBasic.hlsli"
#include "cbuffers.hlsli"
#include "pbrBSDF.hlsli"
#define PI 3.14159265359;

#include "RootSignatures.hlsli"

Texture2D baseTxt : register(t0);
Texture2D normalTxt : register(t1);
//TextureCube env : register(t2);
SamplerState sampl : register(s0);


// sry its pretty messy rn, been experimenting with it a lot
[RootSignature(basicRootSig)]
float4 main(VSOutput input) : SV_Target
{
	float3 baseColorMap = baseTxt.Sample(sampl, -input.texCoord);
	float3 normalMap = normalTxt.Sample(sampl, -input.texCoord).rgb;
	
	float shininess = normalMap.r * normalMap.b;

	float3 N = normalize(input.normal + normalMap);
	float3 V = normalize(eyePos - input.worldPosition);

	float3 reflDir = reflect(normalize(input.worldPosition.xyz - eyePos.xyz), normalize(input.normal));
	//float3 envMap = env.Sample(sampl, reflDir).rgb;

	float metalness = 1.f;

	float roughness = pow(1.0 - shininess, 2);
	float linearRoughness = roughness + 1e-5f;
	float f0 = 0.3f;
	float f90 = 1.f;

	float NdotV = abs(dot(N, V)) + 1e-5f; // avoid artifact (?)

	float3 res = float3(0, 0, 0);
	for (int i = 0; i < nrLights; i++)
	{
		float3 Lunnormalized = lights[i].position - input.worldPosition;
		float3 L = normalize(Lunnormalized);
		float sqrDist = dot(Lunnormalized, Lunnormalized);
		float illuminance = 650.f * (1.f / sqrDist);

		float3 H = normalize(V + L);
		float LdotH = saturate(dot(L, H));
		float NdotH = saturate(dot(N, H));
		float NdotL = saturate(dot(N, L));

		// Specular BRDF
		float3 F = F_Schlick(f0, f90, LdotH);
		float Vis = V_SmithGGXCorrelated(NdotV, NdotL, roughness);
		float D = D_GGX(NdotH, roughness);
		float Fr = D * F * Vis / PI;

		// Diffuse BRDF
		float Fd = Fr_DisneyDiffuse(NdotV, NdotL, LdotH, linearRoughness) / PI;

		res += 
			illuminance * 
			NdotL * 
			(
				(Fd + Fr) * baseColorMap * lights[i].color.rgb
			);
	}

	return float4(res, 1.f);
}
