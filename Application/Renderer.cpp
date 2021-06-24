#include "Renderer.h"

FrameContext frameContext[NUM_FRAMES_IN_FLIGHT] = {};

Renderer::Renderer() {}
Renderer::~Renderer(){}

void Renderer::StartUp(HWND hwnd, Scene* scene)
{
    this->scene = scene;

    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        //::UnregisterClass(wc.lpszClassName, wc.hInstance);
        std::exit(666);
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

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

        using namespace Egg::Math;
        camera = Egg::Cam::FirstPerson::Create()->SetView(Float3(0, 5, -7), Float3(0, 0, 1));
        perFrameCb.CreateResources(device, sizeof(PerFrameCb));
        perObjectCb.CreateResources(device, sizeof(GG::PerObjectCb));
        
        pso = new GG::GPSO(device, rootSig.Get(), vs.Get(), ps.Get());        
    }

    // load a scene
    {
        uint32_t sizeInBytes;
        uint32_t indexDataSizeInBytes;
        uint32_t stride;
        void* indexData;
        void* data;
        DXGI_FORMAT indexFormat;
        {
            std::string path = "../Media/sponza.obj";

            Assimp::Importer importer;

            const aiScene* assimpScene = importer.ReadFile(path, 0);

            ASSERT(assimpScene != nullptr, "Failed to load obj file: '%s'. Assimp error message: '%s'", path.c_str(), importer.GetErrorString());

            ASSERT(assimpScene->HasMeshes(), "Obj file: '%s' does not contain a mesh.", path.c_str());

            for (int i = 0; i < assimpScene->mNumMeshes; ++i)
            {
                // for this example we only load the first mesh
                const aiMesh* assimpMesh = assimpScene->mMeshes[i];

                Mesh mesh;
                mesh.vertices.reserve(assimpMesh->mNumVertices);
                mesh.indices.reserve(assimpMesh->mNumFaces);

                Vertex v;

                for (unsigned int i = 0; i < assimpMesh->mNumVertices; ++i)
                {
                    v.position.x = assimpMesh->mVertices[i].x;
                    v.position.y = assimpMesh->mVertices[i].y;
                    v.position.z = assimpMesh->mVertices[i].z;

                    v.normal.x = assimpMesh->mNormals[i].x;
                    v.normal.y = assimpMesh->mNormals[i].y;
                    v.normal.z = assimpMesh->mNormals[i].z;

                    v.uv.x = assimpMesh->mTextureCoords[0][i].x;
                    v.uv.y = assimpMesh->mTextureCoords[0][i].y;

                    mesh.vertices.emplace_back(v);
                }

                for (unsigned int i = 0; i < assimpMesh->mNumFaces; ++i)
                {
                    aiFace face = assimpMesh->mFaces[i];
                    mesh.indices.emplace_back(face.mIndices[0]);
                    mesh.indices.emplace_back(face.mIndices[1]);
                    mesh.indices.emplace_back(face.mIndices[2]);
                }

                scene->meshes.push_back(mesh);
                
//              assimpScene->mMaterials[1]->

                /*
                aiString texturePath;
        		scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, 0, &texturePath);
                */

                //sizeInBytes = (vertices.size() * sizeof(PNT_Vertex));
                //indexDataSizeInBytes = (indices.size() * 4);
                //stride = sizeof(PNT_Vertex);
                //indexData = &(indices.at(0));
                //data = &(vertices.at(0));
                //indexFormat = DXGI_FORMAT_R32_UINT;
            }
        }
    }

}

void Renderer::UploadTextures()
{
    FrameContext* frameCtx = WaitForNextFrameResources();
    UINT backBufferIdx = swapChain->GetCurrentBackBufferIndex();
    frameCtx->commandAllocator->Reset();

    DX_API("Failed to reset command list (UploadResources)")
        commandList->Reset(frameCtx->commandAllocator, nullptr);

    for (const auto& [id, ent] : entityDirectory) {
        ent->albedo->UploadResources(commandList);
        ent->normal->UploadResources(commandList);
    }

    DX_API("Failed to close command list (UploadResources)")
        commandList->Close();

    ID3D12CommandList* commandLists[] = { commandList };
    commandQueue->ExecuteCommandLists(_countof(commandLists), commandLists);

    UINT64 fenceValue = fenceLastSignaledValue + 1;
    commandQueue->Signal(fence, fenceValue);
    fenceLastSignaledValue = fenceValue;
    frameCtx->fenceValue = fenceValue;
}

void Renderer::Draw()
{
    timestampEnd = clock_type::now();
    dt = std::chrono::duration<float>(timestampEnd - timestampStart).count();
    timestampStart = timestampEnd;
    static double T = 0.0;
    T += dt;
    // update the app
    {
        // perFrameCb
        camera->Animate(dt);
        perFrameCb->viewProjTransform = camera->GetViewMatrix() * camera->GetProjMatrix();
        perFrameCb->rayDirTransform = camera->GetRayDirMatrix();
        perFrameCb->eyePos.xyz = camera->GetEyePosition();
        perFrameCb->eyePos.w = 1.0f;

        /*
        for (int i = 0; i < (*config)["lights"].size(); ++i)
        {

            perFrameCb->lights[i].color = {
                (*config)["lights"][i]["color"][0],
                (*config)["lights"][i]["color"][1],
                (*config)["lights"][i]["color"][2],
                1.0
            };
            perFrameCb->lights[i].position = {
                (*config)["lights"][i]["pos"][0],
                (*config)["lights"][i]["pos"][1],
                (*config)["lights"][i]["pos"][2],
                1.0
            };
        }

        perFrameCb->nrLights = (*config)["lights"].size();
        */

        perFrameCb.Upload();
        
        for (const auto& [id, ent] : entityDirectory)
        {
            perObjectCb->data[id].modelTransform = ent->transform;
            perObjectCb->data[id].modelTransformInverse = ent->transform.Invert();
        }

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

            const float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            commandList->ClearRenderTargetView(rtvHeap->GetCPUHandle(backBufferIdx), clearColor, 0, nullptr);
            commandList->ClearDepthStencilView(dsvHeap->GetCPUHandle(), D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

        }

        heap->BindHeap(commandList);

        // draw
        commandList->SetGraphicsRootSignature(rootSig.Get());
        {
            commandList->SetPipelineState(pso->Get());

            commandList->SetGraphicsRootConstantBufferView(0, perFrameCb.GetGPUVirtualAddress());
            for (const auto& [id,ent] : entityDirectory)
            {
                commandList->SetGraphicsRootConstantBufferView(1, perObjectCb.GetGPUVirtualAddress(id));
                commandList->SetGraphicsRootDescriptorTable(2, heap->GetGPUHandle(2*id));

                ent->geometry->Draw(commandList);
            }
           
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

void Renderer::ShutDown(HWND hwnd)
{
    for (const auto& [id,entity] : entityDirectory)
        delete entity;

    WaitForLastSubmittedFrame();

    // Cleanup
    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    //::UnregisterClass(wc.lpszClassName, wc.hInstance);
}

void Renderer::AddEntity(
    uint32_t id, 
    const std::string& meshPath, 
    const std::string& albedoPath,
    const std::string& normalPath
){
    Entity* e = new Entity{ id, device, heap, meshPath, albedoPath, normalPath };
    entityDirectory.insert({ id, e });
}

void Renderer::Transform(uint32_t id, const Float4x4& transform)
{
    entityDirectory[id]->transform = transform;
}

bool Renderer::CreateDeviceD3D(HWND hWnd)
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

void Renderer::CleanupDeviceD3D()
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

void Renderer::CreateRenderTarget()
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

void Renderer::CleanupRenderTarget()
{
    WaitForLastSubmittedFrame();

    depthStencilBuffer.Reset();

    for (com_ptr<ID3D12Resource>& i : renderTargets) {
        i.Reset();
    }
    renderTargets.clear();
}

void Renderer::WaitForLastSubmittedFrame()
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

FrameContext* Renderer::WaitForNextFrameResources()
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

void Renderer::ResizeSwapChain(HWND hWnd, int width, int height)
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

void Renderer::ProcessMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
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
        return;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return;
        break;
    case WM_DESTROY:
        //app->Destroy();
        ::PostQuitMessage(0);
        return;
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
        camera->ProcessMessage(hWnd, uMsg, wParam, lParam);
        break;
    }
}