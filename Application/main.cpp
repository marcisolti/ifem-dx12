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

void Compute()
{
    /*
    stabilitas -> hullamterjedes
    */
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
    /*
    json 
        configPancakeTurtle, configPancakeDragon, 
        configQStaticTurtleFail, configQStaticTurtleWin,
        configBwEulerTurtleExplodes, configBwEulerTurtleNotExplodes,
        configBwEulerTurtleExplodes2, configQStaticTurtleWin2,
        configBwEulerTurtleExplodes3, 
        
        configBwEulerTurtlePrettyOk, configBwEulerTurtleGetsJittery,
        configNewmark0,
        configBwEulerTurtlePrettyOk2;

    configPancakeTurtle["sim"] = 
    {
        { "integrator", "qStatic" },
        { "stepSize", 0.001 },
        { "magicConstant", 0.0001 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material", 
            {
                {"energyFunction", "ARAP"},
                {"E", 1.0e6},
                {"nu", 0.45},
                {"rho", 500.0},
                {"alpha", 0.1},
                {"beta", 5.0},
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
                            {"t", 100.0},
                            {"f", 0.0}
                        },
                        {
                            {"t", 100.3},
                            {"f", 500'000.0}
                        },
                        {
                            {"t", 1002.5},
                            {"f", 0.0}
                        },
                        {
                            {"t", 100000.0},
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
        },
        {"initConfig", "py"}
    };

    configPancakeDragon["sim"] =
    {
        { "integrator", "qStatic" },
        { "stepSize", 0.001 },
        { "magicConstant", 0.0001 },
        { "numSubsteps",   1 },
        { "model",      "asianDragon" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 1.0e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.2},
                {"beta", 2.0},
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
                            {"t", 100.0},
                            {"f", 0.0}
                        },
                        {
                            {"t", 100.3},
                            {"f", 500'000.0}
                        },
                        {
                            {"t", 1002.5},
                            {"f", 0.0}
                        },
                        {
                            {"t", 100000.0},
                            {"f", 0.0}
                        },
                    }
                },
            },
        },
        { "BCs",
            {
                51,127,178
            }
        },
        {"initConfig", "py"}
    };

    configQStaticTurtleFail["sim"] =
    {
        { "integrator", "qStatic" },
        { "stepSize",   0.01 },
        { "magicConstant", 0.001 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 1.0e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.2},
                {"beta", 2.0},
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
                            {"t", 1.0},
                            {"f", 5000.0}
                        },
                        {
                            {"t", 1.05},
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
        },
        {"initConfig", "r"}
    };

    // works
    configQStaticTurtleWin["sim"] =
    {
        { "integrator", "qStatic" },
        { "stepSize",   0.01 },
        { "magicConstant", 0.000'01 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 1'000'000.0},
                {"nu", 0.35},
                {"rho", 1000.0},
                {"alpha", 0.2},
                {"beta", 2.0},
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
                            {"f", 25000.0}
                        },
                        {
                            {"t", 0.25},
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
        },
        {"initConfig", "r"}
    };

    configBwEulerTurtleExplodes["sim"] =
    {
        { "integrator", "bwEuler" },
        { "stepSize",   0.01 },
        { "magicConstant", 0.01 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 0.2e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.01},
                {"beta", 1.0},
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
                            {"f", -2'500.0}
                        },
                        {
                            {"t", 0.5},
                            {"f", -2'500.0}
                        },
                        {
                            {"t", 0.51},
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
        },
        {"initConfig", "r"}
    };

    configBwEulerTurtleNotExplodes["sim"] =
    {
        { "integrator",     "bwEuler" },
        { "stepSize",       0.001 },
        { "magicConstant",  1.0 },
        { "numSubsteps",    1 },
        { "model",          "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 200'000.0},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.001},
                {"beta", 1.0},
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
                            {"t", 2.0},
                            {"f", 2'500.0}
                        },
                        {
                            {"t", 2.5},
                            {"f", 2'500.0}
                        },
                        {
                            {"t", 2.51},
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
        },
        {"initConfig", "r"}
    };

    configBwEulerTurtleExplodes2["sim"] =
    {
        { "integrator", "bwEuler" },
        { "stepSize",   0.01 },
        { "magicConstant", 0.0001 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 1.0e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.0},
                {"beta", 0.0},
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
                            {"f", 0.0}
                        },
                        {
                            {"t", 0.25},
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
        },
        {"initConfig", "r"}
    };

    configQStaticTurtleWin2["sim"] =
    {
        { "integrator", "qStatic" },
        { "stepSize",   0.01 },
        { "magicConstant", 1.0 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 1.0e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.2},
                {"beta", 2.0},
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
                            {"t", 1.0},
                            {"f", 0.0}
                        },
                        {
                            {"t", 1.05},
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
        },
        {"initConfig", "r"}
    };

    // today
    configBwEulerTurtlePrettyOk["sim"] =
    {
        { "integrator", "bwEuler" },
        { "stepSize",   0.01 },
        { "magicConstant", 1.0 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 0.2e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.1},
                {"beta", 1.0},
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
                            {"t", 1.5},
                            {"f", 5000.0}
                        },
                        {
                            {"t", 2.0},
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
        },
        {"initConfig", "r"}
    };

    // seems like jitteriness introduced by the sudden load decrease
    configBwEulerTurtleGetsJittery["sim"] =
    {
        { "integrator", "bwEuler" },
        { "stepSize",   0.01 },
        { "magicConstant", 1.0 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 0.2e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.1},
                {"beta", 1.0},
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
                            {"t", 1.0},
                            {"f", 5000.0}
                        },
                        {
                            {"t", 1.05},
                            {"f", 0.0}
                        },
                        {
                            {"t", 0.51},
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
        },
        {"initConfig", "r"}
    };

    configNewmark0["sim"] =
    {
        { "integrator", "Newmark" },
        { "stepSize",   0.01 },
        { "magicConstant", 1.0 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 0.2e6},
                {"nu", 0.45},
                {"rho", 1000.0},
                {"alpha", 0.1},
                {"beta", 1.0},
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
                            {"t", 2.0},
                            {"f", 5000.0}
                        },
                        {
                            {"t", 3.0},
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
        },
        {"initConfig", "r"}
    };

    configBwEulerTurtlePrettyOk2["sim"] =
    {
        { "integrator", "bwEuler" },
        { "stepSize",   0.005 },
        { "magicConstant", 1.0 },
        { "numSubsteps",   1 },
        { "model",      "turtle" },
        { "material",
            {
                {"energyFunction", "ARAP"},
                {"E", 10.0e6},
                {"nu", 0.1},
                {"rho", 1000.0},
                {"alpha", 0.1},
                {"beta", 5.0},
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
                            {"t", 0.1},
                            {"f", 100'000.0}
                        },
                        {
                            {"t", 0.2},
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
        },
        {"initConfig", "r"}
    };
    */
    
    const std::string configPath{ "../Media/configs/root.json" };
    std::ifstream i(configPath);
    i >> config;

    std::cout << config << '\n';
    
    std::srand(std::time(nullptr)); // use current time as seed for random generator
    int seed = std::rand();
    config["hello"].push_back( seed );
    // write prettified JSON to another file
    std::ofstream o(configPath);
    o << std::setw(4) << config << std::endl;
    
    
    // Create win32 window
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "ImGui Example", NULL };
    ::RegisterClassEx(&wc);
    HWND hwnd = ::CreateWindow(wc.lpszClassName, "Dear ImGui DirectX12 Example", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

    renderer.StartUp(hwnd, &config);
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

    std::thread simThread{ Compute };

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

    renderer.ProcessMessage(hWnd, msg, wParam, lParam);
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}