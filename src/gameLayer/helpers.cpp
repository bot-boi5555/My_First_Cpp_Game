#include "helpers.h"

Rectangle getTextureAtlas(int x, int y, int cellSizePixelsX, int cellSizePixelsY) {

	Rectangle textureUV = {	
		.x 			= x * (float) cellSizePixelsX,
		.y 			= y * (float) cellSizePixelsY,
		.width 		= (float) cellSizePixelsX,
		.height 	= (float) cellSizePixelsY,
	};

	return textureUV;
}


