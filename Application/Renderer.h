#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx12.h>

#define DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")

#include <Egg/Common.h>
#include <Egg/Shader.h>
#include <Egg/Cam/FirstPerson.h>

#include <GG/ConstantBuffer.hpp>
#include <GG/DescriptorHeap.h>
#include <GG/Geometry.h>
#include <GG/GPSO.h>
#include <GG/Tex2D.h>

#include "ObjLoader.h"

#include <iostream>
#include <chrono>
#include <map>
#include <vector>

#include <thread>

constexpr uint32_t                          NUM_FRAMES_IN_FLIGHT = 3;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

using namespace Egg::Math;

struct Light
{
	Float4 position, color;
};

__declspec(align(256)) struct PerFrameCb {
	Float4x4 viewProjTransform;
	Float4x4 rayDirTransform;
	Float4 eyePos;
	Light lights[64];
	int nrLights;
};

namespace GG
{
	__declspec(align(256)) struct PerObjectCb {
		Float4x4 modelTransform;
		Float4x4 modelTransformInverse;
	};
}

__declspec(align(256)) struct PerObjectCb {
	GG::PerObjectCb data[1024];
};

struct FrameContext
{
	ID3D12CommandAllocator* commandAllocator;
	uint64_t                                fenceValue;
};

struct Entity
{
	GG::Geometry* geometry;
	GG::Tex2D*	  texture;
	Float4x4 transform;
	uint32_t id;

	Entity(uint32_t id, ID3D12Device* device, GG::DescriptorHeap* heap, const std::string& meshPath, const std::string& texturePath)
	{
		this->id = id;
		geometry = new GG::Geometry(device, meshPath);
		texture = new GG::Tex2D(device, heap, texturePath);
		texture->CreateSrv(device, heap, id);
		
		transform = Float4x4::Identity;
	}
	~Entity()
	{
		delete geometry;
		delete texture;
	}

	Entity(uint32_t id, ID3D12Device* device, GG::DescriptorHeap* heap, GG::Geometry* geo, const std::string& texturePath)
	{
		this->id = id;
		geometry = geo;
		texture = new GG::Tex2D(device, heap, texturePath);
		texture->CreateSrv(device, heap, id);

		transform = Float4x4::Identity;
	}
};

class Renderer
{
	ID3D12Device* device = nullptr;

	// --- ----
	// --- COMMAND QUEUE
	// --- ----
	ID3D12CommandQueue* commandQueue = nullptr;

	ID3D12GraphicsCommandList* commandList = nullptr;

	uint32_t                             frameIndex = 0;
	ID3D12Fence* fence = nullptr;
	HANDLE                               fenceEvent = nullptr;
	uint64_t                             fenceLastSignaledValue = 0;

	using clock_type = std::chrono::high_resolution_clock;
	std::chrono::time_point<clock_type> timestampStart;
	std::chrono::time_point<clock_type> timestampEnd;

	IDXGISwapChain3* swapChain = nullptr;
	HANDLE                               swapChainWaitableObject = nullptr;

	// --- ----
	// --- RENDER TARGETS
	// --- ----

	D3D12_VIEWPORT viewPort;
	D3D12_RECT scissorRect;
	// rtv
	uint32_t								NUM_BACK_BUFFERS = 3;
	GG::DescriptorHeap*						rtvHeap;
	std::vector<com_ptr<ID3D12Resource>>	renderTargets;
	GG::DescriptorHeap*						dsvHeap;
	com_ptr<ID3D12Resource>					depthStencilBuffer;

	// --- ----
	// --- RENDERING RESOURCES
	// --- ----
	com_ptr<ID3D12RootSignature>        rootSig;

	Egg::Cam::FirstPerson::P            camera;
	GG::ConstantBuffer<PerFrameCb>      perFrameCb;
	GG::ConstantBuffer<PerObjectCb>     perObjectCb;

	GG::DescriptorHeap* heap;
	GG::DescriptorHeap* appSrvHeap;

	GG::GPSO* pso;
	std::vector<Entity*> entities;
	uint32_t objectCount;

	float dt;

public:

	Renderer() = default;
	~Renderer() = default;

	void StartUp(HWND hwnd);
	void ShutDown(HWND hwnd);

	void Draw();
	void ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	void UploadTextures();

	void AddEntity(const std::string& meshPath, const std::string& texPath);

private:

	bool CreateDeviceD3D(HWND hWnd);
	void CleanupDeviceD3D();
	void CreateRenderTarget();
	void CleanupRenderTarget();
	void WaitForLastSubmittedFrame();
	FrameContext* WaitForNextFrameResources();
	void ResizeSwapChain(HWND hWnd, int width, int height);

};

