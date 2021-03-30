#include "Shader.h"

com_ptr<ID3D12RootSignature> Egg::Shader::LoadRootSignature(ID3D12Device * device, const std::string & filename) {
	com_ptr<ID3DBlob> rootSigBlob = LoadCso(filename);

	return LoadRootSignature(device, rootSigBlob.Get());
}

com_ptr<ID3D12RootSignature> Egg::Shader::LoadRootSignature(ID3D12Device * device, ID3DBlob * blobWithRootSignature) {
	com_ptr<ID3D12RootSignature> rootSig{ nullptr };

	DX_API("Failed to create root signature")
		device->CreateRootSignature(0, blobWithRootSignature->GetBufferPointer(),
									blobWithRootSignature->GetBufferSize(), IID_PPV_ARGS(rootSig.GetAddressOf()));

	return rootSig;
}

com_ptr<ID3DBlob> Egg::Shader::LoadCso(const std::string & filename) {
	std::ifstream file{ filename, std::ios::binary | std::ios::ate };

	ASSERT(file.is_open(), "Failed to open blob file: %s", filename.c_str());

	std::streamsize size = file.tellg();

	file.seekg(0, std::ios::beg);

	com_ptr<ID3DBlob> shaderByteCode{ nullptr };

	DX_API("Failed to allocate memory for blob")
		D3DCreateBlob((size_t)size, shaderByteCode.GetAddressOf());

	if(file.read(reinterpret_cast<char*>(shaderByteCode->GetBufferPointer()), size)) {
		return shaderByteCode;
	} else {
		throw std::exception{ "Failed to load CSO file" };
	}
}