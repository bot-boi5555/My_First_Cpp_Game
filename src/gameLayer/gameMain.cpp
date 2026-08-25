#include "gameMain.h"
#include "assetManager.h"
#include "gameMap.h"
#include "helpers.h"
#include "drawTree.h"

#include <iostream>
#include <algorithm>
#include <fstream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <cstdlib>

#define DELTA_TIME_TOLERANCE 		1.f/5		// max posible delta time
#define PIXELS_PER_BLOCK			32


struct GameData {
	GameMap map;
	Camera2D camera;

} gameData;

AssetManager assetManager;



bool initGame() {

	gameData.map.create(700, 700);

	/*
	for (int y = 0; y < gameData.map.height; ++y) {
		for (int x = 0; x < gameData.map.width; ++x) {
			gameData.map.getBlockUnsafe(x, y).type = Block::stone;
		}
	}
	*/
	
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

	static Block selectedBlock = {.type = Block::grassBlock};

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


	Vector2 worldPos 	= GetScreenToWorld2D(GetMousePosition(), gameData.camera);
	int blockX			= (int) floor(worldPos.x);
	int blockY			= (int) floor(worldPos.y);


	// delete block
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		
		auto block = gameData.map.getBlockSafe(blockX, blockY);

		if (block) {
			*block = {};
		}
		
	}
	// place block
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		
		auto block = gameData.map.getBlockSafe(blockX, blockY);

		if (block) {
			block->type = selectedBlock.type;
		}

		//block->variant = std::rand() % BLOCK_VARIANTS_COUNT;

	}

	
	// simple block selector
	switch (GetKeyPressed()) {
	
		case KEY_ONE:
			selectedBlock.type = Block::woodPlank;
			break;
		
		case KEY_TWO:
			selectedBlock.type = Block::woodLog;
			break;
		
		case KEY_THREE:
			selectedBlock.type = Block::glass;
			break;
		
		case KEY_FOUR:
			selectedBlock.type = Block::bricks;
			break;
		
		case KEY_FIVE:
			selectedBlock.type = Block::leaves;
			break;
		
		case KEY_SIX:
		selectedBlock.type = Block::water;
		break;
		
		case KEY_SEVEN:
			selectedBlock.type = Block::stone;
			break;
		
		case KEY_EIGHT:
			selectedBlock.type = Block::dirt;
			break;
		
		case KEY_NINE:
		selectedBlock.type = Block::grassBlock;
		break;
		
		case KEY_ZERO:
			selectedBlock.type = Block::door;
			break;
		
		default:
		break;
	}


	#pragma region draw world

	BeginMode2D(gameData.camera);

	// render only visible part of screen to improve performance

	Vector2 topLeftView = GetScreenToWorld2D({0, 0}, gameData.camera);
	Vector2 bottomRightView = GetScreenToWorld2D({(float) GetScreenWidth(), (float) GetScreenHeight()}, gameData.camera);

		// padding to ensure the entire visable world is rendered
	int startXView = (int) floorf(topLeftView.x - 1);
	int endXView = (int) floorf(bottomRightView.x + 1);

	int startYView = (int) floorf(topLeftView.y - 1);
	int endYView = (int) floorf(bottomRightView.y + 1);

		// ensure that the start and end values are between 0 and max width / height
	startXView = std::clamp(startXView, 0, gameData.map.width - 1);
	endXView = std::clamp(endXView, 0, gameData.map.width - 1);

	startYView = std::clamp(startYView, 0, gameData.map.height - 1);
	endYView = std::clamp(endYView, 0, gameData.map.height - 1);

	for (int y = startYView; y < endYView; ++y) {
		
		for (int x = startXView; x < endXView; ++x) {

			auto& block = gameData.map.getBlockUnsafe(x, y);

			if (block.type == Block::air) {
				continue;
			}

			float size = 1;
			float posX = x * size;
			float posY = y * size;						
			
			if (block.type == Block::woodLog) {
				drawLog(gameData.map, assetManager, posX, posY, size);
			}
			else {

				DrawTexturePro(
					assetManager.textures, 
					getTextureAtlas(block.type, block.variant, PIXELS_PER_BLOCK, PIXELS_PER_BLOCK), 	// {posX, posY, width, height} (what part of the texture to use from the original png)
					{posX, posY, size, size},												// {posX, posY, width, height} (position and size of the texture to be drawn on the window)
					{0, 0},																	// origin (top left corner)
					0,																		// rotation in degrees
					WHITE																	// tint
				);
			
			}

			

		}
	
	}

	DrawTexturePro(
		assetManager.frame,
		{0, 0, (float) assetManager.frame.width, (float) assetManager.frame.height}, 
		{(float) blockX, (float) blockY, 1, 1},
		{},
		0,
		WHITE
	);


	EndMode2D();	

	#pragma endregion
	
	DrawFPS(10, 10);

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