#include "stone.h"

void Stone::ApplyPhysics(Block (&grid)[gridSize]) {
	this->rect = grid[this->gridIndex].rect;
	grid[this->gridIndex].materialPointer = shared_from_this();
	grid[this->gridIndex].type = StoneType;
	return;
}