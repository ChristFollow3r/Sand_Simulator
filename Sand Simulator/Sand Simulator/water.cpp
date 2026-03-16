#include "water.h"

void Water::ApplyPhysics(Block (&grid)[gridSize]) {

	int random = rand() % 101;

	if (this == nullptr) return;
	if (this->gridIndex + cols >= gridSize) return;
	
	if (grid[this->gridIndex + cols].type == Air) {
		grid[this->gridIndex].type = Air;
		grid[this->gridIndex].materialPointer = nullptr;
		grid[this->gridIndex + cols].type = Type::Water;
		grid[this->gridIndex + cols].materialPointer = shared_from_this();
		this->rect = grid[this->gridIndex + cols].rect;
		this->gridIndex += cols;
	}

	else {

	}

}