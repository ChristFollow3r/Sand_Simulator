#include "sandGrain.h"

void SandGrain::ApplyPhysics(Block(&grid)[gridSize]) {

	int random = rand() % 101;
	//int boundry = sandGrain->gridIndex % 80;

	if (this == nullptr) return;

	if (this->gridIndex + cols >= gridSize) { // Might have to come here later cause if I add various types and ground can't just be sand.
		grid[this->gridIndex].type = Sand;
		grid[this->gridIndex].materialPointer = shared_from_this();
		return;
	}

	if (grid[this->gridIndex + cols].type == Air) {
		grid[this->gridIndex].type = Air;
		grid[this->gridIndex].materialPointer = nullptr;
		this->rect = grid[this->gridIndex + cols].rect;
		grid[this->gridIndex + cols].type = Sand;
		grid[this->gridIndex + cols].materialPointer = shared_from_this();
		this->gridIndex += cols;
	}

	else if (grid[this->gridIndex + cols].type == Sand) {
		if (grid[this->gridIndex + cols - 1].type == Air && grid[this->gridIndex + cols + 1].type == Air) {
			if (random <= 50) {
				grid[this->gridIndex].type = Air;
				grid[this->gridIndex].materialPointer = nullptr;
				this->rect = grid[this->gridIndex + cols - 1].rect;
				grid[this->gridIndex + cols - 1].type = Sand;
				grid[this->gridIndex + cols - 1].materialPointer = shared_from_this();
				this->gridIndex += cols - 1;
				return;
			}
			else if (random > 50) {
				grid[this->gridIndex].type = Air;
				grid[this->gridIndex].materialPointer = nullptr;
				this->rect = grid[this->gridIndex + cols + 1].rect;
				grid[this->gridIndex + cols + 1].type = Sand;
				grid[this->gridIndex + cols + 1].materialPointer = shared_from_this();
				this->gridIndex += cols + 1;
				return;
			}
		}
		else if (grid[this->gridIndex + cols - 1].type == Air && !grid[this->gridIndex + cols + 1].type == Air) {
			grid[this->gridIndex].type = Air;
			grid[this->gridIndex].materialPointer = nullptr;
			this->rect = grid[this->gridIndex + cols - 1].rect;
			grid[this->gridIndex + cols - 1].type = Sand;
			this->gridIndex += cols - 1;
			return;
		}

		else if (!grid[this->gridIndex + cols - 1].type == Air && grid[this->gridIndex + cols + 1].type == Air) {
			grid[this->gridIndex].type = Air;
			grid[this->gridIndex].materialPointer = nullptr;
			this->rect = grid[this->gridIndex + cols + 1].rect;
			grid[this->gridIndex + cols + 1].type = Sand;
			this->gridIndex += cols + 1;
			return;
		}
	}

}