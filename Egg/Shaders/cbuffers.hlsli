struct Light
{
	float4 position, color;
};

cbuffer PerFrameCb : register(b0) {
	float4x4 viewProjMat;
	float4x4 rayDirTransform;
	float4 eyePos;
	Light lights[64];
	int nrLights;
}

/*
cbuffer PerObjectCb : register(b1) {
	float4x4 modelMat;
	float4x4 modelMatInv;
}
*/