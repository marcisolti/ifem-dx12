#pragma once

#include <Egg/Common.h>
#include <Egg/Utility.h>
#include <Egg/Math/Math.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct PNT_Vertex
{
	Egg::Math::Float3 position;
	Egg::Math::Float3 normal;
	Egg::Math::Float2 tex;
};


namespace GG {

	GG_CLASS(Geometry)

		// resources
		com_ptr<ID3D12Resource> vertexBuffer;
		com_ptr<ID3D12Resource> indexBuffer;
		// views
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		D3D12_INDEX_BUFFER_VIEW indexBufferView;
		uint32_t indexCount;

		// properties
		std::vector<D3D12_INPUT_ELEMENT_DESC> inputElements;
		D3D12_INPUT_LAYOUT_DESC inputLayout;
		D3D12_PRIMITIVE_TOPOLOGY topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;


	public:
		
		std::string path;
		std::vector<PNT_Vertex> vertices;
		std::vector<uint32_t> indices;

		Geometry(ID3D12Device* device, std::string filePath, bool deformable = false)
			: path{ filePath }
		{
			// import geometry from file
			
			uint32_t sizeInBytes;
			uint32_t indexDataSizeInBytes;
			uint32_t stride;
			void* indexData;
			void* data;
			DXGI_FORMAT indexFormat;
			{
				std::string path = "../Media/" + filePath;

				Assimp::Importer importer;

				const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords);

				ASSERT(scene != nullptr, "Failed to load obj file: '%s'. Assimp error message: '%s'", path.c_str(), importer.GetErrorString());

				ASSERT(scene->HasMeshes(), "Obj file: '%s' does not contain a mesh.", path.c_str());

				// for this example we only load the first mesh
				const aiMesh* mesh = scene->mMeshes[0];

				indices.reserve(mesh->mNumFaces);
				vertices.reserve(mesh->mNumVertices);

				PNT_Vertex v;

				for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
				{
					v.position.x = mesh->mVertices[i].x;
					v.position.y = mesh->mVertices[i].y;
					v.position.z = mesh->mVertices[i].z;

					v.normal.x = mesh->mNormals[i].x;
					v.normal.y = mesh->mNormals[i].y;
					v.normal.z = mesh->mNormals[i].z;

					v.tex.x = mesh->mTextureCoords[0][i].x;
					v.tex.y = mesh->mTextureCoords[0][i].y;

					vertices.emplace_back(v);
				}

				for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
				{
					aiFace face = mesh->mFaces[i];
					indices.emplace_back(face.mIndices[0]);
					indices.emplace_back(face.mIndices[1]);
					indices.emplace_back(face.mIndices[2]);
				}

				sizeInBytes = (vertices.size() * sizeof(PNT_Vertex));
				indexDataSizeInBytes = (indices.size() * 4);
				stride = sizeof(PNT_Vertex);
				indexData = &(indices.at(0));
				data = &(vertices.at(0));
				indexFormat = DXGI_FORMAT_R32_UINT;
			}

			// create d3d resource
			{
				static int id = 0;

				CD3DX12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_UPLOAD };
				CD3DX12_RESOURCE_DESC vertexBufferSize = CD3DX12_RESOURCE_DESC::Buffer(sizeInBytes);
				CD3DX12_RESOURCE_DESC indexBufferSize = CD3DX12_RESOURCE_DESC::Buffer(indexDataSizeInBytes);

				DX_API("Failed to create vertex buffer (IndexedGeometry)")
					device->CreateCommittedResource(
						&heapProp,
						D3D12_HEAP_FLAG_NONE,
						&vertexBufferSize,
						D3D12_RESOURCE_STATE_GENERIC_READ,
						nullptr,
						IID_PPV_ARGS(vertexBuffer.GetAddressOf())
					);

				DX_API("Failed to create index buffer (IndexedGeometry")
					device->CreateCommittedResource(
						&heapProp,
						D3D12_HEAP_FLAG_NONE,
						&indexBufferSize,
						D3D12_RESOURCE_STATE_GENERIC_READ,
						nullptr,
						IID_PPV_ARGS(indexBuffer.GetAddressOf())
					);

				CD3DX12_RANGE range{ 0,0 };
				void* mappedPtr;

				DX_API("Failed to map vertex buffer (IndexedGeometry)")
					vertexBuffer->Map(0, &range, &mappedPtr);

				memcpy(mappedPtr, data, sizeInBytes);
				vertexBuffer->Unmap(0, nullptr);

				DX_API("Failed to set name for vertex buffer (IndexedGeometry)")
					vertexBuffer->SetName(Egg::Utility::WFormat(L"VB(IndexedGeometry)#%d", id).c_str());

				DX_API("Failed to map index buffer (IndexedGeometry")
					indexBuffer->Map(0, &range, &mappedPtr);

				memcpy(mappedPtr, indexData, indexDataSizeInBytes);
				indexBuffer->Unmap(0, nullptr);

				DX_API("Failed to set name for index buffer (IndexedGeometry)")
					indexBuffer->SetName(Egg::Utility::WFormat(L"IB(IndexedGeometry)#%d", id++).c_str());

				vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
				vertexBufferView.SizeInBytes = sizeInBytes;
				vertexBufferView.StrideInBytes = stride;

				indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
				indexBufferView.Format = indexFormat;
				indexBufferView.SizeInBytes = indexDataSizeInBytes;

				ASSERT(indexFormat == DXGI_FORMAT_R16_UINT || indexFormat == DXGI_FORMAT_R32_UINT, "index format must be DXGI_FORMAT_R16_UINT or DGXI_FORMAT_R32_UINT");

				unsigned int formatSize = (indexFormat == DXGI_FORMAT_R16_UINT) ? 2 : 4;

				ASSERT(indexDataSizeInBytes % formatSize == 0, "index buffer size must be divisible by its format size");

				indexCount = (indexDataSizeInBytes / formatSize);

				inputElements = {
					{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
					{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
					{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
				};

				inputLayout.NumElements = (unsigned int)inputElements.size();
				inputLayout.pInputElementDescs = &(inputElements.at(0));

			}
		}

		Geometry(
			ID3D12Device* device, 
			void* data, 
			uint32_t sizeInBytes, 
			uint32_t stride,
			void* indexData, 
			uint32_t indexDataSizeInBytes, 
			DXGI_FORMAT indexFormat = DXGI_FORMAT_R32_UINT) 
		{
			static int id = 0;
			CD3DX12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_UPLOAD };
			CD3DX12_RESOURCE_DESC vxBufferSize = CD3DX12_RESOURCE_DESC::Buffer(sizeInBytes);
			DX_API("Failed to create vertex buffer (IndexedGeometry)")
				device->CreateCommittedResource(
					&heapProp,
					D3D12_HEAP_FLAG_NONE,
					&vxBufferSize,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(vertexBuffer.GetAddressOf()));

			CD3DX12_RESOURCE_DESC indexBufferSize = CD3DX12_RESOURCE_DESC::Buffer(indexDataSizeInBytes);
			DX_API("Failed to create index buffer (IndexedGeometry")
				device->CreateCommittedResource(
					&heapProp,
					D3D12_HEAP_FLAG_NONE,
					&indexBufferSize,
					D3D12_RESOURCE_STATE_GENERIC_READ,
					nullptr,
					IID_PPV_ARGS(indexBuffer.GetAddressOf()));

			CD3DX12_RANGE range{ 0,0 };
			void* mappedPtr;
			DX_API("Failed to map vertex buffer (IndexedGeometry)")
				vertexBuffer->Map(0, &range, &mappedPtr);

			memcpy(mappedPtr, data, sizeInBytes);
			vertexBuffer->Unmap(0, nullptr);

			DX_API("Failed to set name for vertex buffer (IndexedGeometry)")
				vertexBuffer->SetName(Egg::Utility::WFormat(L"VB(IndexedGeometry)#%d", id).c_str());

			DX_API("Failed to map index buffer (IndexedGeometry")
				indexBuffer->Map(0, &range, &mappedPtr);

			memcpy(mappedPtr, indexData, indexDataSizeInBytes);
			indexBuffer->Unmap(0, nullptr);

			DX_API("Failed to set name for index buffer (IndexedGeometry)")
				indexBuffer->SetName(Egg::Utility::WFormat(L"IB(IndexedGeometry)#%d", id++).c_str());

			vertexBufferView.BufferLocation = vertexBuffer->GetGPUVirtualAddress();
			vertexBufferView.SizeInBytes = sizeInBytes;
			vertexBufferView.StrideInBytes = stride;

			indexBufferView.BufferLocation = indexBuffer->GetGPUVirtualAddress();
			indexBufferView.Format = indexFormat;
			indexBufferView.SizeInBytes = indexDataSizeInBytes;

			ASSERT(indexFormat == DXGI_FORMAT_R16_UINT ||
				indexFormat == DXGI_FORMAT_R32_UINT, "index format must be DXGI_FORMAT_R16_UINT or DGXI_FORMAT_R32_UINT");

			unsigned int formatSize = (indexFormat == DXGI_FORMAT_R16_UINT) ? 2 : 4;

			ASSERT(indexDataSizeInBytes % formatSize == 0, "index buffer size must be divisible by its format size");

			indexCount = (indexDataSizeInBytes / formatSize);
		}

		void SetData(const void* data, unsigned int sizeInBytes) {
			CD3DX12_RANGE readRange{ 0, 0 };
			void* mappedPtr = nullptr;

			DX_API("Failed to map vertex buffer (VertexStreamGeometry)")
				vertexBuffer->Map(0, &readRange, &mappedPtr);

			memcpy(mappedPtr, data, sizeInBytes);
			
			vertexBuffer->Unmap(0, nullptr);
		}

		void SetTopology(D3D12_PRIMITIVE_TOPOLOGY top) { topology = top; }

		D3D12_PRIMITIVE_TOPOLOGY GetTopology() const { return topology; }

		D3D12_PRIMITIVE_TOPOLOGY_TYPE GetTopologyType() const 
		{
			switch (topology) {
			case D3D_PRIMITIVE_TOPOLOGY_POINTLIST:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT;
			case D3D_PRIMITIVE_TOPOLOGY_LINELIST:
			case D3D_PRIMITIVE_TOPOLOGY_LINESTRIP:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE;
			case D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
			case D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ:
			case D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ:
			case D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ:
			case D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ:
			case D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
			default:
				return D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH;
			}
		}

		void AddInputElement(const D3D12_INPUT_ELEMENT_DESC& ied) { inputElements.push_back(ied); }

		void Draw(ID3D12GraphicsCommandList* commandList)
		{
			commandList->IASetPrimitiveTopology(topology);
			commandList->IASetIndexBuffer(&indexBufferView);
			commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
			commandList->DrawIndexedInstanced(indexCount, 1, 0, 0, 0);
		}

		const D3D12_INPUT_LAYOUT_DESC& GetInputLayout() 
		{
			inputLayout.NumElements = (unsigned int)inputElements.size();
			inputLayout.pInputElementDescs = &(inputElements.at(0));
			return inputLayout;
		}

	GG_ENDCLASS
}