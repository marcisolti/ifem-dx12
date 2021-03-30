#pragma once

#include <Egg/Common.h>

namespace GG
{
	class GPSO
	{

		ID3D12PipelineState* gpso;

	public:

		GPSO(
			com_ptr<ID3D12Device> device,
			com_ptr<ID3D12RootSignature> rootSig,
			com_ptr<ID3DBlob> vs,
			com_ptr<ID3DBlob> ps
		)
		{
			D3D12_GRAPHICS_PIPELINE_STATE_DESC gpsoDesc;
			ZeroMemory(&gpsoDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));

			gpsoDesc.pRootSignature = rootSig.Get();
			gpsoDesc.VS = CD3DX12_SHADER_BYTECODE(vs.Get());
			gpsoDesc.PS = CD3DX12_SHADER_BYTECODE(ps.Get());

			// geometry desc
			D3D12_INPUT_ELEMENT_DESC inputElements[] = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
			};

			D3D12_INPUT_LAYOUT_DESC inputLayout;
			inputLayout.NumElements = _countof(inputElements);
			inputLayout.pInputElementDescs = &(inputElements[0]);

			gpsoDesc.InputLayout = inputLayout;
			gpsoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

			gpsoDesc.NumRenderTargets = 1;
			gpsoDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
			gpsoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
			gpsoDesc.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
			gpsoDesc.SampleMask = UINT_MAX;
			gpsoDesc.SampleDesc.Count = 1;
			gpsoDesc.SampleDesc.Quality = 0;
			gpsoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
			gpsoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);

			ID3D12PipelineState* pso;
			DX_API("PSOManager: Failed to create GPSO")
				device->CreateGraphicsPipelineState(&gpsoDesc, IID_PPV_ARGS(&pso));
			
			gpso = pso;
		}

		ID3D12PipelineState* Get() { return gpso; }

	};
}