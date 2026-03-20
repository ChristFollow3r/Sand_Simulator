#include "seed.h"

void Seed::ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions, float dt) {

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


	bool theresWaterAroundDirt = [&]() {
		for (int i = 0; i < 5; i++){

			auto check = [&](int index) {
				return index >= 0 && index < gridSize && grid[index].type == WaterType;
				};

			// Look for WaterType
			if (check(gridIndex + i) ||
				check(gridIndex - i) ||
				check(gridIndex + cols + i) ||
				check(gridIndex + cols - i) || 
				check(gridIndex + (2 * cols) + i) ||
				check(gridIndex + (2 * cols) - i) ||
				check(gridIndex + (3 * cols) + i) ||
				check(gridIndex + (3 * cols) - i))
				return true;

		}
		return false;
	}();


	if (theresWaterAroundDirt && !hasGrown) {

		this->growthRate -= dt;
		int rGrowth = rand() % 60;
		int target = gridIndex - cols + rGrowth;

		if (target < 0 || target >= gridSize) return;

		if (this->growthRate < 0) {
			this->growthRate = rGrowth;
			auto green = std::make_shared<Seed>(grid[target].rect, renderer);
			green->gridIndex = target;
			green->color = { 87, 192, 79, 255 };
			green->hasGrown = true;

			additions.push_back(green);
			this->growthRate = rGrowth;
			this->maxGrowth--;
			if (maxGrowth <= 0) hasGrown = true;
		}
	}

}