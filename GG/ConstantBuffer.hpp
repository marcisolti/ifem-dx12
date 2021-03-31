#pragma once

#include <Egg/Common.h>
#include <Egg/Utility.h>

#include <Egg/Math/Math.h>

#include <sstream>

namespace GG
{
	template <typename T>
	class ConstantBuffer 
	{

		void* mappedPtr;
		D3D12_GPU_VIRTUAL_ADDRESS address;
		uint32_t stride;
		com_ptr<ID3D12Resource> resource;
		T data;

	public:

		ConstantBuffer() {  };

		void CreateResources(ID3D12Device* device, uint32_t stride)
		{
			this->stride = stride;

			CD3DX12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_UPLOAD };
			CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(T));

			DX_API("Failed to create constant buffer resource")
				device->CreateCommittedResource(
					&heapProp,
					D3D12_HEAP_FLAG_NONE,
					&resourceDesc,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(resource.GetAddressOf())
				);

			CD3DX12_RANGE rr(0, 0);
			DX_API("Failed to map constant buffer")
				resource->Map(0, &rr, reinterpret_cast<void**>(&mappedPtr));

			// for debugging purposes, this will name and index the constant buffers for easier identifications
			static int Id = 0;
			std::wstringstream wss;
			wss << "CB(" << typeid(T).name() << ")#" << Id++;
			resource->SetName(wss.str().c_str());

			address = resource->GetGPUVirtualAddress();
		}

		~ConstantBuffer() 
		{
			resource->Unmap(0, nullptr);
			resource.Reset();
			mappedPtr = nullptr;
		}

		void Upload() { memcpy(mappedPtr, &data, sizeof(T)); }

		T& operator=(const T& rhs) { data = rhs; return data; }
		T* operator->() { return &data; }

		D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress(int index = 0) { return address + index * stride; }
	};
}