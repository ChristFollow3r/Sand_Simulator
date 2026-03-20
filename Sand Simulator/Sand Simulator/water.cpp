#include "water.h"

void Water::ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions, float dt) {

	auto moveTo = [&](int targetPosition) {
		grid[this->gridIndex].type = AirType;
		grid[this->gridIndex].materialPointer = nullptr;
		grid[targetPosition].type = WaterType;
		grid[targetPosition].materialPointer = shared_from_this();
		this->rect = grid[targetPosition].rect;
		this->gridIndex = targetPosition;
	};

	int random = rand() % 101;
	if (this == nullptr) return;
	if (this->gridIndex + cols >= gridSize) return;

	if (grid[this->gridIndex + cols].type == AirType) { moveTo(this->gridIndex + cols); return; }

	int col = this->gridIndex % cols;

	if (random > 50) {
		if (grid[(this->gridIndex + cols) + 1].type == AirType && col > 0) { moveTo((this->gridIndex + cols) + 1); return; }
		if (grid[(this->gridIndex + cols) - 1].type == AirType && col < cols - 1) { moveTo((this->gridIndex + cols) - 1); return; }
	}

	else {
		if (grid[this->gridIndex + 1].type == AirType && col < cols - 1) { moveTo(this->gridIndex + 1); return; }
		if (grid[this->gridIndex - 1].type == AirType && col > 0) { moveTo(this->gridIndex - 1); return; }
	}

}