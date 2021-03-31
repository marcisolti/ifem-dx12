#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx12.h>

#define DX12_ENABLE_DEBUG_LAYER
#include <dxgidebug.h>
#pragma comment(lib, "dxguid.lib")

// --- ----
// --- MAIN SYSTEMS
// --- ----

#include <Egg/Common.h>
#include <Egg/Shader.h>
#include <Egg/Cam/FirstPerson.h>

#include <GG/ConstantBuffer.hpp>
#include <GG/DescriptorHeap.h>
#include <GG/Geometry.h>
#include <GG/GPSO.h>
#include <GG/Tex2D.h>

#include <iostream>
#include <chrono>
#include <map>
#include <vector>

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

static ID3D12Device*                device = NULL;

// --- ----
// --- COMMAND QUEUE
// --- ----
static ID3D12CommandQueue*                  commandQueue = nullptr;

struct FrameContext
{
    ID3D12CommandAllocator*                 commandAllocator;
    uint64_t                                fenceValue;
};

constexpr uint32_t                          NUM_FRAMES_IN_FLIGHT = 3;
static FrameContext                         frameContext[NUM_FRAMES_IN_FLIGHT] = {};

static ID3D12GraphicsCommandList*           commandList = nullptr;

static uint32_t                             frameIndex = 0;
static ID3D12Fence*                         fence = nullptr;
static HANDLE                               fenceEvent = nullptr;
static uint64_t                             fenceLastSignaledValue = 0;

using clock_type = std::chrono::high_resolution_clock;
std::chrono::time_point<clock_type> timestampStart;
std::chrono::time_point<clock_type> timestampEnd;

static IDXGISwapChain3*                     swapChain = nullptr;
static HANDLE                               swapChainWaitableObject = nullptr;

// --- ----
// --- RENDER TARGETS
// --- ----

D3D12_VIEWPORT viewPort;
D3D12_RECT scissorRect;
// rtv
constexpr uint32_t                              NUM_BACK_BUFFERS = 3;
GG::DescriptorHeap*                             rtvHeap;
static std::vector<com_ptr<ID3D12Resource>>     renderTargets;
GG::DescriptorHeap*                             dsvHeap;
static com_ptr<ID3D12Resource>                  depthStencilBuffer;

// --- ----
// --- RENDERING RESOURCES
// --- ----
com_ptr<ID3D12RootSignature>        rootSig;

Egg::Cam::FirstPerson::P            camera;
GG::ConstantBuffer<PerFrameCb>      perFrameCb;
GG::ConstantBuffer<PerObjectCb>     perObjectCb;

GG::DescriptorHeap*                 heap;
GG::DescriptorHeap*                 appSrvHeap;

GG::GPSO* pso;
GG::Geometry* geo;
GG::Tex2D* tex;

bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
void WaitForLastSubmittedFrame();
FrameContext* WaitForNextFrameResources();
void ResizeSwapChain(HWND hWnd, int width, int height);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int, char**)
{
    // Create application window
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "ImGui Example", NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, "Dear ImGui DirectX12 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    // init simulator
    /*
        --vmesh
        --smesh
    */

    // Setup Dear ImGui context
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Platform/Renderer backends
        ImGui_ImplWin32_Init(hwnd);
        ImGui_ImplDX12_Init(
            device, NUM_FRAMES_IN_FLIGHT, DXGI_FORMAT_R8G8B8A8_UNORM, 
            appSrvHeap->GetPtr(),
            appSrvHeap->GetCPUHandle(),
            appSrvHeap->GetGPUHandle()
        );
    }

    // init resources
    {
        heap = new GG::DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 2048, true);
        com_ptr<ID3DBlob> vs = Egg::Shader::LoadCso("Shaders/pbrVS.cso");
        com_ptr<ID3DBlob> ps = Egg::Shader::LoadCso("Shaders/pbrPS.cso");
        rootSig = Egg::Shader::LoadRootSignature(device, vs.Get());

        pso = new GG::GPSO(device, rootSig.Get(), vs.Get(), ps.Get());

        camera = Egg::Cam::FirstPerson::Create()->SetView(Float3(0, 5, -7), Float3(0, 0, 1));
        perFrameCb.CreateResources(device, sizeof(PerFrameCb));
        perObjectCb.CreateResources(device, sizeof(GG::PerObjectCb));

        geo = new GG::Geometry(device, "sphere.fbx");
        tex = new GG::Tex2D(device, heap, "checkered.png");
        tex->CreateSrv(device, heap, 0);
    }

    /*
    const std::string id{ "sphere" };
    renderer.AddGeometry(device, id, "sphere.fbx");
    renderer.AddTexture(device, id, "checkered.png");
    physics.AddRigidBody(id, PxTransform{ 0,15,0 }, PxSphereGeometry(2.5f), true);

    const std::string id1{ "light1" };
    renderer.AddLight(id1, Float3{ 20,20,20 });
    physics.AddRigidBody(id1, PxTransform{ 10,10,10 }, PxSphereGeometry(1.f), true);
    */

    // upload textures
    {
        FrameContext* frameCtx = WaitForNextFrameResources();
        UINT backBufferIdx = swapChain->GetCurrentBackBufferIndex();
        frameCtx->commandAllocator->Reset();

        DX_API("Failed to reset command list (UploadResources)")
            commandList->Reset(frameCtx->commandAllocator, nullptr);

        tex->UploadResources(commandList);
            
        DX_API("Failed to close command list (UploadResources)")
            commandList->Close();

        ID3D12CommandList* commandLists[] = { commandList };
        commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

        UINT64 fenceValue = fenceLastSignaledValue + 1;
        commandQueue->Signal(fence, fenceValue);
        fenceLastSignaledValue = fenceValue;
        frameCtx->fenceValue = fenceValue;
    }

    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    bool load = true;

    float dt;
    timestampStart = clock_type::now();
    timestampEnd = timestampStart;

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        // imgue
        {
            // Poll and handle messages (inputs, window resize, etc.)
            // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
            // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
            // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
            // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
            if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
            {
                ::TranslateMessage(&msg);
                ::DispatchMessage(&msg);
                continue;
            }

            // Start the Dear ImGui frame
            ImGui_ImplDX12_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();

            // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
            if (show_demo_window)
                ImGui::ShowDemoWindow(&show_demo_window);

            // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
                ImGui::Checkbox("Another Window", &show_another_window);
                ImGui::Checkbox("Load sim", &load);

                ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

                if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                    counter++;
                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);

                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
                ImGui::End();
            }

            // 3. Show another simple window.
            if (show_another_window)
            {
                ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
                ImGui::Text("Hello from another window!");
                ImGui::End();
            }

            // Rendering
            ImGui::Render();
        }

        timestampEnd = clock_type::now();
        dt = std::chrono::duration<float>(timestampEnd - timestampStart).count();
        timestampStart = timestampEnd;

        //thread 1                  thread 2
                            /*
                            * draw static geometry
                            * if(new) copy_geo
                            * draw dynamic geometry
                            */

        // step simulator
        /*
            <-bcs
            <-loads
            ->displacements
        */
        
        // draw result
        /*
         * update vertices
         * update normals
         * new = true
         */


         
        // update the app
        {
            // perFrameCb
            camera->Animate(dt);
            perFrameCb->viewProjTransform = camera->GetViewMatrix() * camera->GetProjMatrix();
            perFrameCb->rayDirTransform = camera->GetRayDirMatrix();
            perFrameCb->eyePos.xyz = camera->GetEyePosition();
            perFrameCb->eyePos.w = 1.0f;

            int i = 0;
            perFrameCb->lights[0].color = { 1,1,1,1 };
            perFrameCb->lights[0].position = { 10,10,10,1 };
            i++;
            perFrameCb->nrLights = i;

            perFrameCb.Upload();

            perObjectCb->data[0].modelTransform = Float4x4::Identity;
            perObjectCb->data[0].modelTransformInverse = Float4x4::Identity;

            perObjectCb.Upload();
        }
        // populate command list and render
        {
            FrameContext* frameCtx = WaitForNextFrameResources();
            uint32_t backBufferIdx = swapChain->GetCurrentBackBufferIndex();
            {
                frameCtx->commandAllocator->Reset();

                CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
                    renderTargets[backBufferIdx].Get(),
                    D3D12_RESOURCE_STATE_PRESENT,
                    D3D12_RESOURCE_STATE_RENDER_TARGET
                );
                commandList->Reset(frameCtx->commandAllocator, NULL);
                commandList->ResourceBarrier(1, &barrier);

            }

            // render target setup
            {
                commandList->RSSetViewports(1, &viewPort);
                commandList->RSSetScissorRects(1, &scissorRect);

                CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle{ rtvHeap->GetCPUHandle(backBufferIdx) };
                CD3DX12_CPU_DESCRIPTOR_HANDLE dsvHandle{ dsvHeap->GetCPUHandle() };

                commandList->OMSetRenderTargets(1, &rtvHandle, FALSE, &dsvHandle);

                //const float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
                commandList->ClearRenderTargetView(rtvHeap->GetCPUHandle(backBufferIdx), clear_color.data(), 0, nullptr);
                commandList->ClearDepthStencilView(dsvHeap->GetCPUHandle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

            }

            heap->BindHeap(commandList);

            // draw
            commandList->SetGraphicsRootSignature(rootSig.Get());
            {
                commandList->SetPipelineState(pso->Get());

                commandList->SetGraphicsRootConstantBufferView(0, perFrameCb.GetGPUVirtualAddress());
                commandList->SetGraphicsRootConstantBufferView(1, perObjectCb.GetGPUVirtualAddress());
                commandList->SetGraphicsRootDescriptorTable(2,heap->GetGPUHandle(0));

                geo->Draw(commandList);
            }

            appSrvHeap->BindHeap(commandList);
            ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList);

            // syncing
            {
                CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(
                    renderTargets[backBufferIdx].Get(),
                    D3D12_RESOURCE_STATE_RENDER_TARGET,
                    D3D12_RESOURCE_STATE_PRESENT
                );

                commandList->ResourceBarrier(1, &barrier);

                DX_API("Failed to close command list")
                    commandList->Close();

                ID3D12CommandList* cLists[] = { commandList };
                commandQueue->ExecuteCommandLists(_countof(cLists), cLists);

                DX_API("Failed to present swap chain")
                    swapChain->Present(1, 0);
                // Sync
                UINT64 fenceValue = fenceLastSignaledValue + 1;
                commandQueue->Signal(fence, fenceValue);
                fenceLastSignaledValue = fenceValue;
                frameCtx->fenceValue = fenceValue;

            }

        }
    }

    WaitForLastSubmittedFrame();

    // Cleanup
    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}
// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC1 sd;
    {
        ZeroMemory(&sd, sizeof(sd));
        sd.BufferCount = NUM_BACK_BUFFERS;
        sd.Width = 0;
        sd.Height = 0;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        sd.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
        sd.Scaling = DXGI_SCALING_STRETCH;
        sd.Stereo = FALSE;
    }

    // [DEBUG] Enable debug interface
#ifdef DX12_ENABLE_DEBUG_LAYER
    ID3D12Debug* pdx12Debug = NULL;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&pdx12Debug))))
        pdx12Debug->EnableDebugLayer();
#endif

    // Create device
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
    if (D3D12CreateDevice(NULL, featureLevel, IID_PPV_ARGS(&device)) != S_OK)
        return false;

    // [DEBUG] Setup debug interface to break on any warnings/errors
#ifdef DX12_ENABLE_DEBUG_LAYER
    if (pdx12Debug != NULL)
    {
        ID3D12InfoQueue* pInfoQueue = NULL;
        device->QueryInterface(IID_PPV_ARGS(&pInfoQueue));
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_CORRUPTION, true);
        pInfoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
        pInfoQueue->Release();
        pdx12Debug->Release();
    }
#endif


    appSrvHeap = new GG::DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 1, true);

    // command queue
    {
        D3D12_COMMAND_QUEUE_DESC desc = {};
        desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
        desc.NodeMask = 1;
        if (device->CreateCommandQueue(&desc, IID_PPV_ARGS(&commandQueue)) != S_OK)
            return false;
    }

    // command allocator, command list, fence, fenceevent
    {
        for (UINT i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
            if (device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&frameContext[i].commandAllocator)) != S_OK)
                return false;

        if (device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, frameContext[0].commandAllocator, NULL, IID_PPV_ARGS(&commandList)) != S_OK ||
            commandList->Close() != S_OK)
            return false;

        if (device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)) != S_OK)
            return false;

        fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (fenceEvent == NULL)
            return false;
    }

    // create swap chain for hwnd
    {
        IDXGIFactory4* dxgiFactory = NULL;
        IDXGISwapChain1* swapChain1 = NULL;
        if (CreateDXGIFactory1(IID_PPV_ARGS(&dxgiFactory)) != S_OK ||
            dxgiFactory->CreateSwapChainForHwnd(commandQueue, hWnd, &sd, NULL, NULL, &swapChain1) != S_OK ||
            swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain)) != S_OK)
            return false;
        swapChain1->Release();
        dxgiFactory->Release();
        swapChain->SetMaximumFrameLatency(NUM_BACK_BUFFERS);
        swapChainWaitableObject = swapChain->GetFrameLatencyWaitableObject();
    }

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (swapChain) { swapChain->Release(); swapChain = nullptr; }
    if (swapChainWaitableObject != nullptr) { CloseHandle(swapChainWaitableObject); }
    for (uint32_t i = 0; i < NUM_FRAMES_IN_FLIGHT; i++)
        if (frameContext[i].commandAllocator) { frameContext[i].commandAllocator->Release(); frameContext[i].commandAllocator = nullptr; }
    if (commandQueue) { commandQueue->Release(); commandQueue = nullptr; }
    if (commandList) { commandList->Release(); commandList = nullptr; }
    if (fence) { fence->Release(); fence = nullptr; }
    if (fenceEvent) { CloseHandle(fenceEvent); fenceEvent = nullptr; }
    if (device) { device->Release(); device = nullptr; }

#ifdef DX12_ENABLE_DEBUG_LAYER
    IDXGIDebug1* pDebug = nullptr;
    if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&pDebug))))
    {
        pDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY);
        pDebug->Release();
    }
#endif

}

void CreateRenderTarget()
{

    // viewport, scissor
    {
        DXGI_SWAP_CHAIN_DESC scDesc;
        swapChain->GetDesc(&scDesc);


        viewPort.TopLeftX = 0;
        viewPort.TopLeftY = 0;
        viewPort.Width = (float)scDesc.BufferDesc.Width;
        viewPort.Height = (float)scDesc.BufferDesc.Height;
        viewPort.MinDepth = 0.0f;
        viewPort.MaxDepth = 1.0f;

        scissorRect.left = 0;
        scissorRect.top = 0;
        scissorRect.right = scDesc.BufferDesc.Width;
        scissorRect.bottom = scDesc.BufferDesc.Height;
    }

    // Create Render Target View Descriptor Heap, like a RenderTargetView** on the GPU. A set of pointers.
    rtvHeap = new GG::DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, NUM_BACK_BUFFERS);

    // Create Render Target Views
    {
        renderTargets.resize(NUM_BACK_BUFFERS);

        for (unsigned int i = 0; i < NUM_BACK_BUFFERS; ++i) {
            DX_API("Failed to get swap chain buffer")
                swapChain->GetBuffer(i, IID_PPV_ARGS(renderTargets[i].GetAddressOf()));

            device->CreateRenderTargetView(renderTargets[i].Get(), nullptr, rtvHeap->GetCPUHandle(i));
        }

    }


    // Depth stencil
    {
        dsvHeap = new GG::DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV);

        D3D12_CLEAR_VALUE depthOptimizedClearValue = {};
        depthOptimizedClearValue.Format = DXGI_FORMAT_D32_FLOAT;
        depthOptimizedClearValue.DepthStencil.Depth = 1.0f;
        depthOptimizedClearValue.DepthStencil.Stencil = 0;

        CD3DX12_HEAP_PROPERTIES heapProp{ D3D12_HEAP_TYPE_DEFAULT };
        CD3DX12_RESOURCE_DESC resourceDesc = CD3DX12_RESOURCE_DESC::Tex2D(DXGI_FORMAT_D32_FLOAT, scissorRect.right, scissorRect.bottom, 1, 0, 1, 0, D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL);

        DX_API("Failed to create Depth Stencil buffer")
            device->CreateCommittedResource(
                &heapProp,
                D3D12_HEAP_FLAG_NONE,
                &resourceDesc,
                D3D12_RESOURCE_STATE_DEPTH_WRITE,
                &depthOptimizedClearValue,
                IID_PPV_ARGS(depthStencilBuffer.GetAddressOf())
            );

        depthStencilBuffer->SetName(L"Depth Stencil Buffer");

        D3D12_DEPTH_STENCIL_VIEW_DESC depthStencilDesc = {};
        depthStencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
        depthStencilDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        depthStencilDesc.Flags = D3D12_DSV_FLAG_NONE;

        device->CreateDepthStencilView(depthStencilBuffer.Get(), &depthStencilDesc, dsvHeap->GetCPUHandle());
    }
}

void CleanupRenderTarget()
{
    WaitForLastSubmittedFrame();

    depthStencilBuffer.Reset();

    for (com_ptr<ID3D12Resource>& i : renderTargets) {
        i.Reset();
    }
    renderTargets.clear();
}

void WaitForLastSubmittedFrame()
{
    FrameContext* frameCtx = &frameContext[frameIndex % NUM_FRAMES_IN_FLIGHT];

    UINT64 fenceValue = frameCtx->fenceValue;
    if (fenceValue == 0)
        return; // No fence was signaled

    frameCtx->fenceValue = 0;
    if (fence->GetCompletedValue() >= fenceValue)
        return;

    fence->SetEventOnCompletion(fenceValue, fenceEvent);
    WaitForSingleObject(fenceEvent, INFINITE);
}

FrameContext* WaitForNextFrameResources()
{
    UINT nextFrameIndex = frameIndex + 1;
    frameIndex = nextFrameIndex;

    HANDLE waitableObjects[] = { swapChainWaitableObject, NULL };
    DWORD numWaitableObjects = 1;

    FrameContext* frameCtx = &frameContext[nextFrameIndex % NUM_FRAMES_IN_FLIGHT];
    UINT64 fenceValue = frameCtx->fenceValue;
    if (fenceValue != 0) // means no fence was signaled
    {
        frameCtx->fenceValue = 0;
        fence->SetEventOnCompletion(fenceValue, fenceEvent);
        waitableObjects[1] = fenceEvent;
        numWaitableObjects = 2;
    }

    WaitForMultipleObjects(numWaitableObjects, waitableObjects, TRUE, INFINITE);

    return frameCtx;
}

void ResizeSwapChain(HWND hWnd, int width, int height)
{
    DXGI_SWAP_CHAIN_DESC1 sd;
    swapChain->GetDesc1(&sd);
    sd.Width = width;
    sd.Height = height;

    IDXGIFactory4* dxgiFactory = NULL;
    swapChain->GetParent(IID_PPV_ARGS(&dxgiFactory));

    swapChain->Release();
    CloseHandle(swapChainWaitableObject);

    IDXGISwapChain1* swapChain1 = NULL;
    dxgiFactory->CreateSwapChainForHwnd(commandQueue, hWnd, &sd, NULL, NULL, &swapChain1);
    swapChain1->QueryInterface(IID_PPV_ARGS(&swapChain));
    swapChain1->Release();
    dxgiFactory->Release();

    swapChain->SetMaximumFrameLatency(NUM_BACK_BUFFERS);

    swapChainWaitableObject = swapChain->GetFrameLatencyWaitableObject();
    assert(swapChainWaitableObject != NULL);
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (device != NULL && wParam != SIZE_MINIMIZED)
        {
            WaitForLastSubmittedFrame();
            ImGui_ImplDX12_InvalidateDeviceObjects();
            CleanupRenderTarget();
            ResizeSwapChain(hWnd, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam));
            CreateRenderTarget();
            ImGui_ImplDX12_CreateDeviceObjects();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        //app->Destroy();
        ::PostQuitMessage(0);
        return 0;
    case WM_KEYDOWN:
    case WM_KEYUP:
    case WM_MOUSEMOVE:
    case WM_MOUSEWHEEL:
    case WM_KILLFOCUS:
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONDOWN:
    case WM_MBUTTONUP:
    case WM_RBUTTONDOWN:
    case WM_RBUTTONUP:
        camera->ProcessMessage(hWnd, msg, wParam, lParam);
        break;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}