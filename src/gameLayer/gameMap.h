#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <vector>
#include "blocks.h"

struct GameMap
{
	int width = 0;
	int height = 0;

	std::vector<Block> mapData;


	void create(int width, int height);

	Block &getBlockUnsafe(int x, int y);
	Block *getBlockSafe(int x, int y);			// check if we did not go out of bounds

};


#endif