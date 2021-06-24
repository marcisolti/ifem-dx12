#pragma once
#define NOMINMAX
#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx12.h>

#include <vector>
#include <iomanip>
#include <fstream>
#include "Renderer.h"

#include "Scene.h"

class App
{
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	std::map<uint32_t, Entity*>* entityDirectoryRef;

	Scene* scene;

public:
	App();
	~App();

	void StartUp(Renderer* renderer, Scene* scene);
	void Update();

};

