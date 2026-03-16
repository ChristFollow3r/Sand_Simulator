#include "water.h"

void Water::ApplyPhysics(Block (&grid)[gridSize]) {

	int random = rand() % 101;

	if (this == nullptr) return;

	if (this->gridIndex + cols >= gridSize) return; //Prevents nullpointer acces error

	if (grid[this->gridIndex + 1].type != Air
		&& grid[this->gridIndex - 1].type != Air && grid[this->gridIndex + cols + 1].type != Air && grid[this->gridIndex + cols - 1].type != Air) return;

	if (grid[this->gridIndex + cols].type == Air) { // Falls 
		grid[this->gridIndex].type = Air;
		grid[this->gridIndex].materialPointer = nullptr;
		grid[this->gridIndex + cols].type = Type::WaterType;
		grid[this->gridIndex + cols].materialPointer = shared_from_this();
		this->rect = grid[this->gridIndex + cols].rect;
		this->gridIndex += cols;
		return;
	}

	if (this->gridIndex + cols == gridSize) {
		if (random > 50) {
			if (this->gridIndex + 1 >= gridSize) return;
			grid[this->gridIndex].type = Air;
			grid[this->gridIndex].materialPointer = nullptr;
			grid[this->gridIndex + 1].type = Type::WaterType;
			grid[this->gridIndex + 1].materialPointer = shared_from_this();
			this->rect = grid[this->gridIndex + 1].rect;
			this->gridIndex += 1;
		}
		else {
			if (this->gridIndex - 1 < 0) return;
			grid[this->gridIndex].type = Air;
			grid[this->gridIndex].materialPointer = nullptr;
			grid[this->gridIndex - 1].type = Type::WaterType;
			grid[this->gridIndex - 1].materialPointer = shared_from_this();
			this->rect = grid[this->gridIndex - 1].rect;
			this->gridIndex -= 1;
		}
 	}
	

	if (this->gridIndex + (cols - 1) < 0 || this->gridIndex + (cols + 1) >= gridSize) return; //Prevents mullpointer acces error

	else if (grid[(this->gridIndex + cols) - 1].type != Air && grid[(this->gridIndex + cols) + 1].type == Air) { // Move down right
		grid[this->gridIndex].type = Air;
		grid[this->gridIndex].materialPointer = nullptr;
		grid[(this->gridIndex + cols) + 1].type = Type::WaterType;
		grid[(this->gridIndex + cols) + 1].materialPointer = shared_from_this();
		this->rect = grid[(this->gridIndex + cols) + 1].rect;
		this->gridIndex += (cols + 1);
		return;
	}

	else if (grid[(this->gridIndex + cols) + 1].type != Air && grid[(this->gridIndex + cols) - 1].type == Air) { // Move down left
		grid[this->gridIndex].type = Air;
		grid[this->gridIndex].materialPointer = nullptr;
		grid[(this->gridIndex + cols) - 1].type = Type::WaterType;
		grid[(this->gridIndex + cols) - 1].materialPointer = shared_from_this();
		this->rect = grid[(this->gridIndex + cols) - 1].rect;
		this->gridIndex += (cols - 1);
		return;
	}

	else  { // Move left or right

		if (random > 50) {

			if (this->gridIndex + 1 >= gridSize || grid[this->gridIndex + 1].type != Air) return;
			else {
				grid[this->gridIndex].type = Air;
				grid[this->gridIndex].materialPointer = nullptr;
				grid[this->gridIndex + 1].type = Type::WaterType;
				grid[this->gridIndex + 1].materialPointer = shared_from_this();
				this->rect = grid[this->gridIndex + 1].rect;
				this->gridIndex += 1;
				return;
			}
		}

		else {

			if (this->gridIndex - 1 < 0 || grid[this->gridIndex - 1].type != Air) return;
			else {
				grid[this->gridIndex].type = Air;
				grid[this->gridIndex].materialPointer = nullptr;
				grid[this->gridIndex - 1].type = Type::WaterType;
				grid[this->gridIndex - 1].materialPointer = shared_from_this();
				this->rect = grid[this->gridIndex - 1].rect;
				this->gridIndex -= 1;
				return;
			}
		}
	}

}