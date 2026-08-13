#include <iostream>

#include <raylib.h>

#include <imgui.h>
#include <rlImGui.h>

int main(int argc, char* argv[]) {

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(800, 450, "First window");

	rlImGuiSetup(true); // setup rlimgui

	Color myColor = {.r = 255, .g = 0 , .b = 200, .a = 255};

	while(!WindowShouldClose()) {

		BeginDrawing();

		ClearBackground(RAYWHITE);

		rlImGuiBegin(); // run rlimgui


		DrawText("Great, you drew on the screen with raylib", 180, 200, 20, myColor);

		DrawRectangle(50, 50, 100, 100, {255, 0, 0, 127});
		DrawRectangle(75, 75, 100, 100, {0, 255, 0, 127});
		
		DrawRectangle(10, 350, 100, 100, {35, 175, 255, 255});

		ImGui::ShowDemoWindow();

		/*
		ImGui::Begin("Test"); 	// all beginnings

		ImGui::Text("Hello");
		ImGui::Button("Click Me");

		ImGui::End();			// must come to an end (Free yo memory)

		*/

		rlImGuiEnd();

		EndDrawing();

	}

	rlImGuiShutdown();

	CloseWindow();

	return 0;
}