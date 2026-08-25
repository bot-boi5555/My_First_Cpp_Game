#include "drawTree.h"

#include "helpers.h"
#include "assetManager.h"

#define PIXELS_PER_BLOCK 32

enum LogType {
	normal,
	leftRightLeaves,
	rightLeaves,
	leftLeaves,
	base,
	topLeaves,
	topNoLeaves,
	stump
};


void drawLog(GameMap& map, AssetManager assetManager, int x, int y, int size) {

	Block* topBlock 	= map.getBlockSafe(x, y - 1);
	Block* bottomBlock 	= map.getBlockSafe(x, y + 1);
	Block* leftBlock	= map.getBlockSafe(x - 1, y);
	Block* rightBlock	= map.getBlockSafe(x + 1, y);
	Block* treeLog	= map.getBlockSafe(x, y);

	Rectangle atlasPosition = {};

	if (!treeLog) {
		return;
	}

	atlasPosition.y = 0;

	if (topBlock && topBlock->type == Block::leaves) {
		atlasPosition.x = LogType::topLeaves;
	}
	else if (leftBlock && rightBlock && leftBlock->type ==  Block::leaves && rightBlock->type ==  Block::leaves) {
		atlasPosition.x = LogType::leftRightLeaves;
	}
	else if (rightBlock && rightBlock->type ==  Block::leaves) {
		atlasPosition.x = LogType::rightLeaves;
	}
	else if (leftBlock && leftBlock->type ==  Block::leaves) {
		atlasPosition.x = LogType::leftLeaves;
	}
	else if (topBlock && bottomBlock && topBlock->type == Block::woodLog && bottomBlock->type != Block::air && bottomBlock->type != Block::woodLog) {
		atlasPosition.x = LogType::base;
	}
	else if (bottomBlock && bottomBlock->type != Block::air && bottomBlock->type != Block::woodLog) {
		atlasPosition.x = LogType::stump;
	}
	else if (bottomBlock && (topBlock && bottomBlock->type == Block::woodLog && topBlock->type == Block::air || !topBlock) ) {
		atlasPosition.x = LogType::topNoLeaves;
	}
	else {
		atlasPosition.x = LogType::normal;
	}
	
	DrawTexturePro(
				assetManager.treeTextures, 
				getTextureAtlas(atlasPosition.x, atlasPosition.y, PIXELS_PER_BLOCK, PIXELS_PER_BLOCK), 	
				{(float) x, (float) y, (float) size, (float) size},												
				{0, 0},																	
				0,																		
				WHITE																	
			);

}