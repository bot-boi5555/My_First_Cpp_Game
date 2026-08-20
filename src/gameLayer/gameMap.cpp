#include "gameMap.h"

#include <asserts.h>


void GameMap::create(int width, int height) {

	*this = {}; // clear all data

	mapData.resize(width * height);

	this->width = width;
	this->height = height;

	// auto will automatically detect the type (Texture)
	for (auto& e : mapData) {
		e = {};					// clear block data
	}

}


Block& GameMap::getBlockUnsafe(int x, int y) {

	permaAssertCommentDevelopement(mapData.size() == width * height, "Map not initialized.");

	permaAssertCommentDevelopement(x >= 0 && y >= 0 && x < width && y < height, "Out of bounds error.");

	return mapData[y * width + x];
}


Block* GameMap::getBlockSafe(int x, int y) {
	
	permaAssertCommentDevelopement(mapData.size() == width * height, "Map not initialized.");

	if (x < 0 || y < 0 || x >= width || y >= height) {
		return nullptr;
	}

	return &mapData[y * width + x];
}