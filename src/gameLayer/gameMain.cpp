#include "gameMain.h"
#include "assetManager.h"
#include "gameMap.h"
#include "helpers.h"

#include <iostream>
#include <fstream>
#include <raylib.h>
#include <cmath>

#define DELTA_TIME_TOLERANCE 		1.f/5		// max posible delta time
#define PIXELS_PER_BLOCK			32

struct GameData {
	GameMap map;
	Camera2D camera;

} gameData;

AssetManager assetManager;



bool initGame() {

	gameData.map.create(30, 30);

	
	gameData.map.getBlockUnsafe(0, 0).type 	= Block::water;
	gameData.map.getBlockUnsafe(1, 1).type 	= Block::grassBlock;
	gameData.map.getBlockUnsafe(2, 2).type 	= Block::pearlStone;
	gameData.map.getBlockUnsafe(3, 3).type 	= Block::uraniumBlock;
	gameData.map.getBlockUnsafe(4, 4).type 	= Block::glassPane;
	

	/*
	// flat world
	for (int x = 0; x < gameData.map.width; ++x) {
		for (int y = 0; y < gameData.map.height; ++y) {

			if (y == 0) {
				gameData.map.getBlockUnsafe(x, y).type = Block::grassBlock;
			}
			else {
				gameData.map.getBlockUnsafe(x, y).type = Block::dirt;
			}

		}
	}
	*/

	/*
	// right triangle
	for (int y = 0; y < gameData.map.height; ++y) {
		for (int x = 0; x <= y; ++ x) {

			if (y == x) {
				gameData.map.getBlockUnsafe(x, y).type = Block::grassBlock;
			}
			else {
				gameData.map.getBlockUnsafe(x, y).type = Block::dirt;
			}


		}
	}
	*/

	/*
	for (int y = 0; y < gameData.map.height; ++y) {
		for (int x = 0; x < gameData.map.width; ++x) {

			if (x % 4 == 0 && y %4 == 0) {
				gameData.map.getBlockUnsafe(x, y).type = Block::blueRubyBlock;
			}
			else if (x % 4 == 0) {
				gameData.map.getBlockUnsafe(x, y).type = Block::goldBlock;
			}
			else if (y % 4 == 0) {
				gameData.map.getBlockUnsafe(x, y).type = Block::copperBlock;
			}
			
		}
	}
	*/


	/*
	for (int y = 0; y < gameData.map.height; ++y) {
		for (int x = 0; x < gameData.map.width; ++x) {

			float sinFunc = (std::sin(x) + std::sin(2*x) + 1) / 6;

			if (0.5 * gameData.map.height - gameData.map.height * 0.3 * sinFunc < y) {
				gameData.map.getBlockUnsafe(x, y).type = Block::dirt;
			}

		}
	}
	*/
	

	gameData.camera.target 					= {0, 0};			// puts the map (0, 0) in the center of the screen
	gameData.camera.zoom 					= 100;
	gameData.camera.rotation				= 0;

	assetManager.loadAll();


	return true;
}


bool updateGame() {
	
	float deltaTime = GetFrameTime();			// in general, multiply movement related stuff with delta time


	if (deltaTime > DELTA_TIME_TOLERANCE) {		// ensure that the jump between renders is not large
		deltaTime = DELTA_TIME_TOLERANCE;
	}

	gameData.camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f}; 


	ClearBackground({75, 75, 150, 255});

	#pragma region camera movement

	if (IsKeyDown(KEY_LEFT)) {
		gameData.camera.target.x -= 7 * deltaTime;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		gameData.camera.target.x += 7 * deltaTime;
	}
	if (IsKeyDown(KEY_UP)) {
		gameData.camera.target.y -= 7 * deltaTime;
	}
	if (IsKeyDown(KEY_DOWN)) {
		gameData.camera.target.y += 7 * deltaTime;
	}

	#pragma endregion

	BeginMode2D(gameData.camera);


	for (int y = 0; y < gameData.map.height; ++y) {
		
		for (int x = 0; x < gameData.map.width; ++x) {

			auto& block = gameData.map.getBlockUnsafe(x, y);

			if (block.type == Block::air) {
				continue;
			}

			float size = 1;
			float posX = x * size;
			float posY = y * size;						
			

			DrawTexturePro(
				assetManager.textures, 
				getTextureAtlas(block.type, 0, PIXELS_PER_BLOCK, PIXELS_PER_BLOCK), 	// {posX, posY, width, height} (what part of the texture to use from the original png)
				{posX, posY, size, size},												// {posX, posY, width, height} (position and size of the texture to be drawn on the window)
				{0, 0},																	// origin (top left corner)
				0,																		// rotation in degrees
				WHITE																	// tint
			);


		}
	
	}


	EndMode2D();	
	

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