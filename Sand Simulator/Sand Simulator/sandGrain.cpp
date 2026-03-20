#include "sandGrain.h"

void SandGrain::ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions) {

	int random = rand() % 101;

	auto moveTo = [&](int targetPosition) {

		if (targetPosition < 0 || targetPosition >= gridSize) return;
		if (grid[targetPosition].type == WaterType) {
			grid[this->gridIndex].type = grid[targetPosition].type; // It gets its type
			grid[this->gridIndex].materialPointer = grid[targetPosition].materialPointer; // It becomes the thing that wants to go to
			grid[this->gridIndex].materialPointer->gridIndex = this->gridIndex; // It gets its index
			grid[this->gridIndex].materialPointer->rect = grid[this->gridIndex].rect; // It gets its rect
		}
		else {
			grid[this->gridIndex].type = AirType;
			grid[this->gridIndex].materialPointer = nullptr;
		}
		grid[targetPosition].type = SandType;
		grid[targetPosition].materialPointer = shared_from_this();
		this->rect = grid[targetPosition].rect;
		this->gridIndex = targetPosition;

		};

	if (gridIndex + cols >= gridSize) return;
	if (grid[this->gridIndex + cols].type == AirType) moveTo(this->gridIndex + cols);

	else {

		bool leftfree = grid[this->gridIndex + cols - 1].type == AirType || grid[this->gridIndex + cols - 1].type == WaterType;
		bool rightfree = grid[this->gridIndex + cols + 1].type == AirType || grid[this->gridIndex + cols + 1].type == WaterType;

		if (leftfree && rightfree) {
			if (random <= 50) moveTo(this->gridIndex + cols - 1);
			else moveTo(this->gridIndex + cols + 1);
		}

		else if (leftfree) moveTo(this->gridIndex + cols - 1);
		else if (rightfree) moveTo(this->gridIndex + cols + 1);

	}

}


