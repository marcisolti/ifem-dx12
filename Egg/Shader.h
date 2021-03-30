#pragma once

#include "Common.h"
#include <fstream>

namespace Egg {
	
	class Shader {
		Shader() = delete;
		~Shader() = delete;
	public:

		static com_ptr<ID3D12RootSignature> LoadRootSignature(ID3D12Device * device, const std::string & filename);

		static com_ptr<ID3D12RootSignature> LoadRootSignature(ID3D12Device * device, ID3DBlob * blobWithRootSignature);

		static com_ptr<ID3DBlob> LoadCso(const std::string & filename);

	};

}
