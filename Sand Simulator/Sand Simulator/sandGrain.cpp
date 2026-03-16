#include "sandGrain.h"

void SandGrain::ApplyPhysics(Block(&grid)[gridSize]) {

	int random = rand() % 101;
	//int boundry = sandGrain->gridIndex % 80;

	if (this == nullptr) return;

	if (this->gridIndex + cols >= gridSize) return;

	if (grid[this->gridIndex + cols].type == AirType) {
		grid[this->gridIndex].type = AirType;
		grid[this->gridIndex].materialPointer = nullptr;
		grid[this->gridIndex + cols].type = SandType;
		grid[this->gridIndex + cols].materialPointer = shared_from_this();
		this->rect = grid[this->gridIndex + cols].rect;
		this->gridIndex += cols;
	}

	else if (grid[this->gridIndex + cols].type == WaterType) {
		grid[this->gridIndex].type = WaterType;
		grid[this->gridIndex].materialPointer = grid[this->gridIndex + cols].materialPointer;
		grid[this->gridIndex].materialPointer->gridIndex = this->gridIndex;
		grid[this->gridIndex].materialPointer->rect = grid[this->gridIndex].rect;

		grid[this->gridIndex + cols].type = SandType;
		grid[this->gridIndex + cols].materialPointer = shared_from_this();
		this->rect = grid[this->gridIndex + cols].rect;
		this->gridIndex += cols;
	}

	else if (grid[this->gridIndex + cols].type != AirType) { // Change this eventually so it can go through water

		bool leftFree = grid[this->gridIndex + cols - 1].type == AirType || grid[this->gridIndex + cols - 1].type == WaterType;
		bool rightFree = grid[this->gridIndex + cols + 1].type == AirType || grid[this->gridIndex + cols + 1].type == WaterType;


		if (leftFree && rightFree) {
			if (random <= 50) {
				grid[this->gridIndex].type = AirType;
				grid[this->gridIndex].materialPointer = nullptr;
				grid[this->gridIndex + cols - 1].type = SandType;
				grid[this->gridIndex + cols - 1].materialPointer = shared_from_this();
				this->rect = grid[this->gridIndex + cols - 1].rect;
				this->gridIndex += cols - 1;
				return;
			}
			else if (random > 50) {
				grid[this->gridIndex].type = AirType;
				grid[this->gridIndex].materialPointer = nullptr;
				grid[this->gridIndex + cols + 1].type = SandType;
				grid[this->gridIndex + cols + 1].materialPointer = shared_from_this();
				this->rect = grid[this->gridIndex + cols + 1].rect;
				this->gridIndex += cols + 1;
				return;
			}
		}
		else if (leftFree) {
			grid[this->gridIndex].type = AirType;
			grid[this->gridIndex].materialPointer = nullptr;
			grid[this->gridIndex + cols - 1].type = SandType;
			this->rect = grid[this->gridIndex + cols - 1].rect;
			this->gridIndex += cols - 1;
			return;
		}

		else if (rightFree) {
			grid[this->gridIndex].type = AirType;
			grid[this->gridIndex].materialPointer = nullptr;
			grid[this->gridIndex + cols + 1].type = SandType;
			this->rect = grid[this->gridIndex + cols + 1].rect;
			this->gridIndex += cols + 1;
			return;
		}
	}

}