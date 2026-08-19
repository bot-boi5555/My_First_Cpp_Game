#ifndef BLOCKS_H
#define BLOCKS_H

#include <cstdint>

struct Block {
	
	enum {
		air = 0,
		dirt,

		BLOCKS_COUNT
	};
	
	std::uint16_t type = 0;
};



#endif