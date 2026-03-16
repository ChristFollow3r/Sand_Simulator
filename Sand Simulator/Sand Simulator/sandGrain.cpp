#include "sandGrain.h"

void SandGrain::ApplyPhysics(Block(&grid)[gridSize]) {

	int random = rand() % 101;
	//int boundry = sandGrain->gridIndex % 80;

	if (this == nullptr) return;

	if (this->gridIndex + cols >= gridSize) return;

	if (grid[this->gridIndex + cols].type == Air) {
		grid[this->gridIndex].type = Air;
		grid[this->gridIndex].materialPointer = nullptr;
		grid[this->gridIndex + cols].type = Sand;
		grid[this->gridIndex + cols].materialPointer = shared_from_this();
		this->rect = grid[this->gridIndex + cols].rect;
		this->gridIndex += cols;
	}

	else if (grid[this->gridIndex + cols].type != Air) { // Change this eventually so it can go through water
		if (grid[this->gridIndex + cols - 1].type == Air && grid[this->gridIndex + cols + 1].type == Air) {
			if (random <= 50) {
				grid[this->gridIndex].type = Air;
				grid[this->gridIndex].materialPointer = nullptr;
				grid[this->gridIndex + cols - 1].type = Sand;
				grid[this->gridIndex + cols - 1].materialPointer = shared_from_this();
				this->rect = grid[this->gridIndex + cols - 1].rect;
				this->gridIndex += cols - 1;
				return;
			}
			else if (random > 50) {
				grid[this->gridIndex].type = Air;
				grid[this->gridIndex].materialPointer = nullptr;
				grid[this->gridIndex + cols + 1].type = Sand;
				grid[this->gridIndex + cols + 1].materialPointer = shared_from_this();
				this->rect = grid[this->gridIndex + cols + 1].rect;
				this->gridIndex += cols + 1;
				return;
			}
		}
		else if (grid[this->gridIndex + cols - 1].type == Air && !grid[this->gridIndex + cols + 1].type == Air) {
			grid[this->gridIndex].type = Air;
			grid[this->gridIndex].materialPointer = nullptr;
			grid[this->gridIndex + cols - 1].type = Sand;
			this->rect = grid[this->gridIndex + cols - 1].rect;
			this->gridIndex += cols - 1;
			return;
		}

		else if (!grid[this->gridIndex + cols - 1].type == Air && grid[this->gridIndex + cols + 1].type == Air) {
			grid[this->gridIndex].type = Air;
			grid[this->gridIndex].materialPointer = nullptr;
			grid[this->gridIndex + cols + 1].type = Sand;
			this->rect = grid[this->gridIndex + cols + 1].rect;
			this->gridIndex += cols + 1;
			return;
		}
	}

}