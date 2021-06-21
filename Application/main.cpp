#include "App.h"
App app;

#include "Renderer.h"
Renderer renderer;

#include "Simulator.h"
Simulator sim;

std::vector<double> results;

#include "Common/nlohmann/json.hpp"
using json = nlohmann::json;

#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace Egg::Math;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow)
{
    json config;
        
    const std::string configPath{ "../Media/configs/root.json" };
    std::ifstream i(configPath);
    i >> config;
    
    // Create win32 window
    ImGui_ImplWin32_EnableDpiAwareness();
    
    const wchar_t windowClassName[] = L"WindowClass";
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = Instance;
    wc.lpszClassName = (LPCWSTR)&windowClassName;

    RegisterClassExW(&wc);
    HWND hwnd = ::CreateWindowExW(
        0,
        windowClassName, 
        L"𝕴𝖓𝖙𝖊𝖗𝖆𝖈𝖙𝖎𝖛𝖊 𝐅𝐄𝐌 😁", 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720,
        NULL, 
        NULL, 
        Instance, 
        NULL
    );

    renderer.StartUp(hwnd, &config);

    config["solverTime"] = 0.0;
    app.StartUp(&renderer, &config);

    // parse for scene
    for (int i = 0; i < config["scene"].size(); ++i)
    {
        const uint32_t id = i + 1;
        renderer.AddEntity(
            id, 
            config["scene"][i]["mesh"], 
            config["scene"][i]["texture"]
        );
        
        renderer.Transform(
            id, 
            Float4x4::Translation({
                config["scene"][i]["transform"][0],
                config["scene"][i]["transform"][1],
                config["scene"][i]["transform"][2] 
            })
        );

    }

    sim.StartUp(&renderer, &config);

    renderer.Transform(
        0, 
        Float4x4::Rotation(
            { 0, 1, 0 }, 
            3.14156
        )
    );



    renderer.UploadTextures();

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // Our state
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

        app.Update();
        sim.Update();
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

    sim.ProcessMessage(hWnd, msg, wParam, lParam);
    renderer.ProcessMessage(hWnd, msg, wParam, lParam);
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}