#pragma once

#include <Egg/Common.h>
#include <DirectXTex/DirectXTex.h>

#include <string>

#include "DescriptorHeap.h"

namespace GG
{
	GG_CLASS(Tex2D)

		com_ptr<ID3D12Resource> resource;
		com_ptr<ID3D12Resource> uploadResource;
		D3D12_RESOURCE_DESC rdsc;

		bool uploaded; // <- is it a hack? 

	public:

		int index;
		std::string path;

		Tex2D(ID3D12Device* device, GG::DescriptorHeap::A heap, const std::string &filePath)
			:path{ filePath }, uploaded{false}
		{
			// create resource for texture uploading
			{
				std::wstring wstr = Egg::Utility::WFormat(L"../Media/%S", filePath.c_str());

				DirectX::TexMetadata metaData;
				DirectX::ScratchImage sImage;

				DX_API("Failed to load image: %s", filePath.c_str())
					DirectX::LoadFromWICFile(wstr.c_str(), 0, &metaData, sImage);

				ZeroMemory(&rdsc, sizeof(D3D12_RESOURCE_DESC));
				rdsc.DepthOrArraySize = 1;
				rdsc.Height = (unsigned int)metaData.height;
				rdsc.Width = (unsigned int)metaData.width;
				rdsc.Format = metaData.format;
				rdsc.MipLevels = 1;
				rdsc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				rdsc.Alignment = 0;
				rdsc.SampleDesc.Count = 1;
				rdsc.SampleDesc.Quality = 0;
				rdsc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
				rdsc.Flags = D3D12_RESOURCE_FLAG_NONE;

				CD3DX12_HEAP_PROPERTIES defaultHeapProp{ D3D12_HEAP_TYPE_DEFAULT };
				CD3DX12_HEAP_PROPERTIES uploadHeapProp{ D3D12_HEAP_TYPE_UPLOAD };

				DX_API("failed to create committed resource for texture file")
					device->CreateCommittedResource(
						&defaultHeapProp,
						D3D12_HEAP_FLAG_NONE,
						&rdsc,
						D3D12_RESOURCE_STATE_COPY_DEST,
						nullptr,
						IID_PPV_ARGS(resource.GetAddressOf())
					);

				UINT64 copyableSize;
				device->GetCopyableFootprints(&rdsc, 0, 1, 0, nullptr, nullptr, nullptr, &copyableSize);

				CD3DX12_RESOURCE_DESC copyableSizeDesc = CD3DX12_RESOURCE_DESC::Buffer(copyableSize);

				DX_API("failed to create committed resource for texture file (upload buffer)")
					device->CreateCommittedResource(
						&uploadHeapProp,
						D3D12_HEAP_FLAG_NONE,
						&copyableSizeDesc,
						D3D12_RESOURCE_STATE_GENERIC_READ,
						nullptr,
						IID_PPV_ARGS(uploadResource.GetAddressOf()));

				CD3DX12_RANGE readRange{ 0,0 };
				void* texPtr;

				DX_API("Failed to map upload resource")
					uploadResource->Map(0, &readRange, &texPtr);

				memcpy(texPtr, sImage.GetPixels(), sImage.GetPixelsSize());

				uploadResource->Unmap(0, nullptr);
			}
		}	

		void CreateSrv(ID3D12Device* device, GG::DescriptorHeap::P heap, int index)
		{

			D3D12_SHADER_RESOURCE_VIEW_DESC srvd;
			ZeroMemory(&srvd, sizeof(D3D12_SHADER_RESOURCE_VIEW_DESC));
			srvd.Format = rdsc.Format;
			srvd.Texture2D.MipLevels = rdsc.MipLevels;
			srvd.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
			srvd.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
			
			this->index = index;
			heap->CreateSrv(device, resource.Get(), &srvd, index);
		
		}

		void UploadResources(ID3D12GraphicsCommandList* commandList)
		{
			if (!uploaded) // <- it does look like one
			{
				CD3DX12_TEXTURE_COPY_LOCATION dst{ resource.Get(), 0 };
				D3D12_PLACED_SUBRESOURCE_FOOTPRINT psf;
				psf.Offset = 0;
				psf.Footprint.Depth = 1;
				psf.Footprint.Height = rdsc.Height;
				psf.Footprint.Width = rdsc.Width;
				psf.Footprint.RowPitch = (DirectX::BitsPerPixel(rdsc.Format) / 8U) * rdsc.Width;
				psf.Footprint.Format = rdsc.Format;
				CD3DX12_TEXTURE_COPY_LOCATION src{ uploadResource.Get(), psf };
				commandList->CopyTextureRegion(&dst, 0, 0, 0, &src, nullptr);

				CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
					resource.Get(),
					D3D12_RESOURCE_STATE_COPY_DEST,
					D3D12_RESOURCE_STATE_GENERIC_READ
				);

				commandList->ResourceBarrier(1, &barrier);
				uploaded = true;
			}
		}

		int GetIndex() { return index; }

	GG_ENDCLASS
}