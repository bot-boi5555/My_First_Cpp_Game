#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <raylib.h>

struct AssetManager {
	
	Texture2D dirt = {};
	Texture2D textures = {};
	
	void loadAll();
};

#endif