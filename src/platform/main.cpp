#include <iostream>

#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

#include <imGuiThemes.h>
#include <gameMain.h>

#define MAX_FPS 240

int main(int argc, char* argv[]) {

	#if PRODUCTION_BUILD == 1
		SetTraceLogLevel(LOG_NONE);
	#endif


	float num2 = 0;

	// raylib config
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "First window");
	SetExitKey(KEY_NULL);					// ESC no longer shuts the window
	SetTargetFPS(MAX_FPS);						// fps to max out

	#pragma region imgui_setup

	rlImGuiSetup(true); // setup rlimgui

	ImGuiIO& io = ImGui::GetIO();

	#pragma region custom style 
	
	imGuitheme1();

	#pragma endregion

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; 	// allow for keyboard control
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; 	// allow for gamepad (ps/xbox controller) control
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; 		// allows for imgui windows to be docked on other imgui window
	io.FontGlobalScale = 2.5; 								// increase the font size by a factor

	#pragma endregion

	
	// initialize game
	if (!initGame()) {
		return 0;
	}


	while(!WindowShouldClose()) {

		BeginDrawing();

		ClearBackground(BLACK);

		#pragma region imgui

		rlImGuiBegin(); // run rlimgui
		
		// makes imgui bg see-through (without this, it will be gray)
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport()); // allows imGui windows to be docked on the main raylib window
		
		ImGui::PopStyleColor(2); // part of the see-through code


		#pragma endregion

		if(!updateGame()) {
			CloseWindow();  // close window instead of return 0 because we may have some game functions (save, etc) that needs to be done
		}


		#pragma region imgui_windows

		
		#pragma endregion


		#pragma region imgui

		rlImGuiEnd();
		
		#pragma endregion

		EndDrawing();

	}

	CloseWindow();

	closeGame();

	#pragma region imgui
	rlImGuiShutdown();
	#pragma endregion



	return 0;
}