#include "stone.h"

void Stone::ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions) {
	this->rect = grid[this->gridIndex].rect;
	grid[this->gridIndex].materialPointer = shared_from_this();
	grid[this->gridIndex].type = StoneType;
	return;
}