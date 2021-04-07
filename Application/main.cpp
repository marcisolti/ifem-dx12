#include "App.h"
App app;

#include "Renderer.h"
Renderer renderer;

#include "Simulator.h"
Simulator sim;

std::vector<double> results;

void Compute()
{
    sim.Step();
}

using namespace Egg::Math;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int, char**)
{
    // Create win32 window
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "ImGui Example", NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, "Dear ImGui DirectX12 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    renderer.StartUp(hwnd);
    app.StartUp();

    //renderer.AddEntity("sphere.fbx", "checkered.png");
    //renderer.AddEntity("bunny.obj", "bunnybase.png");
    sim.StartUp(&renderer, "turtle");

    renderer.UploadTextures();

    std::thread t1{ Compute };
    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // Our state
    int displayIndex = 0;
    int frameCount = 0;
    while (msg.message != WM_QUIT)
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

        sim.Step();
        app.Update(displayIndex, frameCount);
        sim.SetDisplayIndex(displayIndex);
        if(frameCount == displayIndex)
            displayIndex++;
        frameCount++;
        renderer.Draw();

    }

    renderer.ShutDown(hwnd);

    return 0;
}

// Helper functions

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    renderer.ProcessMessage(hWnd, msg, wParam, lParam);
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}