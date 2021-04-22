#include "App.h"
App app;

#include "Renderer.h"
Renderer renderer;

#include "Simulator.h"
Simulator sim;

std::vector<double> results;

#include "Common/nlohmann/json.hpp"
using json = nlohmann::json;

void Compute()
{
    while(1)
    {
        sim.Step();
    }
}

using namespace Egg::Math;

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int main(int, char**)
{
    json config;
    config["sim"] = 
    {
        { "integrator", "1" },
        { "stepSize",   0.01},
        { "numSubsteps",   5},
        { "model",      "turtle" },
        { "material", 
            {
                {"energyFunction", "ARAP"},
                {"E", 1.0e6},
                {"nu", 0.45},
                {"rho", 1000.0}
            }
        },
        { "loadCases",
            {
                { "nodes", { 3 * 296 + 2 }},
                { "loadSteps", 
                    {
                        {
                            {"t", 0.0},
                            {"f", 0.0}
                        },
                        {
                            {"t", 0.2},
                            {"f", 50'000.0}
                        },
                        {
                            {"t", 0.3},
                            {"f", 0.0}
                        },
                        {
                            {"t", 2.5},
                            {"f", 0.0}
                        },
                        {
                            {"t", 100.0},
                            {"f", 0.0}
                        },
                    }
                },
            },
        },
        { "BCs", 
            {
                1, 3, 6, 8, 11, 12, 13, 15,
                17, 18, 26, 29, 42, 45, 47,
                49, 58, 59, 60, 247, 248,
                256, 265
            }
        }
    };

    // Create win32 window
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "ImGui Example", NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, "Dear ImGui DirectX12 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    renderer.StartUp(hwnd);
    app.StartUp();

    //renderer.AddEntity("sphere.fbx", "checkered.png");
    //renderer.AddEntity("bunny.obj", "bunnybase.png");
    sim.StartUp(&renderer, config);

    renderer.UploadTextures();

    std::thread t1{ Compute };
    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    // Our state
    int displayIndex = 0;
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

        int frameCount = sim.GetStepNum();
        app.Update(&displayIndex, frameCount);
        sim.SetDisplayIndex(displayIndex);
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