#include "gameMain.h"
#include "assetManager.h"

#include <iostream>
#include <fstream>
#include <raylib.h>

#define DELTA_TIME_TOLERANCE 		1.f/5		// max posible delta time

struct GameData {
	
} gameData;

AssetManager assetManager;

bool initGame() {

	assetManager.loadAll();

	return true;
}


bool updateGame() {
	
	float deltaTime = GetFrameTime();			// in general, multiply movement related stuff with delta time


	if (deltaTime > DELTA_TIME_TOLERANCE) {		// ensure that the jump between renders is not large
		deltaTime = DELTA_TIME_TOLERANCE;
	}


	
	DrawTexturePro(
		assetManager.dirt, 
		{0, 0, (float) assetManager.dirt.width, (float) assetManager.dirt.height}, 	// {posX, posY, sizeX, sizeY} (what part of the texture to use from the original png)
		{50, 50, 100, 100},																	// {posX, posY, sizeX, sizeY} (position and size of the texture to be drawn on the window)
		{},
		0,
		WHITE
	);

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