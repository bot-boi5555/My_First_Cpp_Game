#include "gameMain.h"

#include <iostream>
#include <fstream>
#include <raylib.h>

#define DELTA_TIME_TOLERANCE 		1.f/5		// max posible delta time

struct GameData {
	float positionX = 100;
	float positionY = 100;
} gameData;


bool initGame() {
	return true;
}


bool updateGame() {

	Color myColor = {.r = 255, .g = 0 , .b = 200, .a = 255};
	
	float deltaTime = GetFrameTime();			// in general, multiply movement related stuff with delta time
	int speed = 200;

	if (deltaTime > DELTA_TIME_TOLERANCE) {		// ensure that the jump between renders is not large
		deltaTime = DELTA_TIME_TOLERANCE;
	}

	if (IsKeyDown(KEY_A)) {
		gameData.positionX -= speed * deltaTime;
	}
	if (IsKeyDown(KEY_D)) {
		gameData.positionX += speed * deltaTime;
	}
	if (IsKeyDown(KEY_S)) {
		gameData.positionY += speed * deltaTime;
	}
	if (IsKeyDown(KEY_W)) {
		gameData.positionY -= speed * deltaTime;
	}

	DrawRectangle(gameData.positionX, gameData.positionY, 50, 50, myColor);

	return true;
}


bool closeGame() {
	
	// this will work on vscode since the console on vs code does not close
	std::cout << "GAME CLOSED\n";

	// this is vscode is not ide that is used
	std::ofstream endFile(RESOURCES_PATH "endFile.txt");
	endFile << "GAME CLOSED\n";
	endFile.close();

	return true;
}