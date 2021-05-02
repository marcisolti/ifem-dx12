#include "App.h"

App::App() {}
App::~App() {}

void App::StartUp(Renderer* renderer, json* config)
{
    this->config = config;
    entityDirectoryRef = &(renderer->entityDirectory);

}

void App::Update(int* displayIndex, int frameCount)
{
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

        ImGui::SliderInt("Frame", displayIndex, 0, frameCount-1);

        static bool playing = false;
        if (ImGui::Button("Play/Pause"))
            playing = !playing;

        static int multiplier = 1;
        ImGui::InputInt("timestep size", &multiplier);


        if (playing && (*displayIndex + multiplier < frameCount - 1))
            (*displayIndex) += multiplier;

        for (const auto& [id, ent] : *entityDirectoryRef)
        {
            char buffer[128];
            sprintf(buffer, "entity_%d", id);
            if (ImGui::TreeNode(buffer))
            {

                ImGui::Text("id: %d", id);


                ImGui::TreePop();
            }
        }

        ImGui::Separator();

        for (int i = 0; i < (*config)["lights"].size(); ++i)
        {
            char buffer[128];
            sprintf(buffer, "light_%d", i);
            if (ImGui::TreeNode(buffer))
            {

                ImVec4 lightColor = ImVec4{
                    (*config)["lights"][i]["color"][0],
                    (*config)["lights"][i]["color"][1],
                    (*config)["lights"][i]["color"][2],
                    1.0
                };

                ImVec4 lightPos = ImVec4{
                    (*config)["lights"][i]["pos"][0],
                    (*config)["lights"][i]["pos"][1],
                    (*config)["lights"][i]["pos"][2],
                    1.0
                };
                
                ImGui::ColorEdit3("color", (float*)&lightColor); // Edit 3 floats representing a color
                ImGui::DragFloat3("position", (float*)&lightPos);

                (*config)["lights"][i]["pos"][0] = lightPos.x;
                (*config)["lights"][i]["pos"][1] = lightPos.y;
                (*config)["lights"][i]["pos"][2] = lightPos.z;

                (*config)["lights"][i]["color"][0] = lightColor.x;
                (*config)["lights"][i]["color"][1] = lightColor.y;
                (*config)["lights"][i]["color"][2] = lightColor.z;

                ImGui::TreePop();
            }
        }
        

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);


        if (ImGui::TreeNode("Demo stuff"))
        {

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);


            ImGui::TreePop();
            ImGui::Separator();
        }

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