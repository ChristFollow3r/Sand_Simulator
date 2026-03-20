#include "seed.h"

void Seed::ApplyPhysics(Block* grid) {

	int random = rand() % 101;

	auto moveTo = [&](int targetPosition) {

		if (targetPosition < 0 || targetPosition >= gridSize) return;
		if (grid[targetPosition].type == AirType) {
			grid[this->gridIndex].type = AirType;
			grid[this->gridIndex].materialPointer = nullptr;

			grid[targetPosition].type = SeedType;
			grid[targetPosition].materialPointer = shared_from_this();
			this->rect = grid[targetPosition].rect;
			this->gridIndex = targetPosition;
			return;
		}
	};

	if (this->gridIndex + cols >= gridSize) return;
	if (grid[this->gridIndex + cols].type == AirType) moveTo(gridIndex + cols);

	else {
		bool checkLeft = grid[this->gridIndex + cols - 1].type == AirType;
		bool checkRight = grid[this->gridIndex + cols + 1].type == AirType;

		if (checkLeft && checkRight) {
			if (random <= 50) moveTo(gridIndex + cols + 1);
			else moveTo(gridIndex + cols - 1);
		}
		if (checkRight) moveTo(gridIndex + cols + 1);
		if (checkLeft) moveTo(gridIndex + cols - 1);
	}


	bool theresWater = [&]() {
		for (int i = 0; i < 5; i++){

			// Bound Checks
			if (gridIndex + i >= gridSize || gridIndex + cols + i >= gridSize ||
				gridIndex + (2 + cols) + i >= gridSize ||
				gridIndex + (3 + cols) + i >= gridSize) continue;
			if (gridIndex - i < 0) continue;


			// Look for WaterType
			if (grid[this->gridIndex + i].type == WaterType ||
				grid[this->gridIndex - i].type == WaterType ||
				grid[this->gridIndex + cols + i].type == WaterType ||
				grid[this->gridIndex + cols - i].type == WaterType ||
				grid[this->gridIndex + (2 * cols) + i].type == WaterType ||
				grid[this->gridIndex + (2 * cols) - i].type == WaterType ||
				grid[this->gridIndex + (3 * cols) + i].type == WaterType ||
				grid[this->gridIndex + (3 * cols) - i].type == WaterType
				) return true;

		}
		return false;
	}();

	if (theresWater) {
		for (int i = 1; i < 7; i++)
		{	
			int target = gridIndex - cols * i;
		}
	}

}