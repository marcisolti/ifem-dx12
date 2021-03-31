#pragma once

#include <Egg/Common.h>
#include <Egg/Utility.h>

#include <map>
#include <string>


namespace GG 
{
	class DescriptorHeap 
	{
		com_ptr<ID3D12DescriptorHeap> resource;
		D3D12_DESCRIPTOR_HEAP_TYPE type;
		uint32_t numDescriptors;
		CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle;
		CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle;
		uint32_t increment;

	public:
		DescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors = 1, bool shaderVisible = false)
		: numDescriptors{ numDescriptors }, type{ type }
		{
			// create descriptor heap
			D3D12_DESCRIPTOR_HEAP_DESC dhd;
			dhd.NodeMask = 0;
			dhd.NumDescriptors = numDescriptors;
			dhd.Type = type;
			dhd.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

			DX_API("Failed to create descriptor heap for texture")
				device->CreateDescriptorHeap(&dhd, IID_PPV_ARGS(resource.GetAddressOf()));

			gpuHandle = resource->GetGPUDescriptorHandleForHeapStart();
			cpuHandle = resource->GetCPUDescriptorHandleForHeapStart();

			increment = device->GetDescriptorHandleIncrementSize(type);
		}

		~DescriptorHeap() { resource.Reset(); }

		void CreateSrv(ID3D12Device* device, ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC* srvd, int index)
		{
			device->CreateShaderResourceView(resource, srvd, GetCPUHandle(index));
		}

		void BindHeap(ID3D12GraphicsCommandList* commandList) 
		{
			commandList->SetDescriptorHeaps(1, resource.GetAddressOf());
		}

		ID3D12DescriptorHeap* GetPtr() { return resource.Get(); }

		CD3DX12_GPU_DESCRIPTOR_HANDLE GetGPUHandle(int index = 0) { return CD3DX12_GPU_DESCRIPTOR_HANDLE{ gpuHandle, index * (int)increment }; }
		CD3DX12_CPU_DESCRIPTOR_HANDLE GetCPUHandle(int index = 0) { return CD3DX12_CPU_DESCRIPTOR_HANDLE{ cpuHandle, index * (int)increment }; }

	};
}