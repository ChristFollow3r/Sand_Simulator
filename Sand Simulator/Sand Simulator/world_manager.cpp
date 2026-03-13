#include "world_manager.h"

float deltaTime(Uint64& lastTick) {

	Uint64 currentTick = SDL_GetTicks(); // Example: 5 ---> 6
	Uint64 elapsedTick = currentTick - lastTick; // Example: 5 - 4 ----> 6 - 5 ...
	lastTick = currentTick; // 5

	return static_cast<float>(elapsedTick / 1000.0);
}

void AssignBlockRects(Block(&grid)[4800]) {

	float x = 0;
	float y = 0;
	float height = 10;
	float width = 10;

	int rowOffset = 60;
	int offset = 80;

	for (int i = 0; i < rowOffset; i++)
	{
		for (int j = 0; j < offset; j++)
		{
			SDL_FRect newRect = { x, y, height, width };
			grid[i * offset + j].rect = newRect;
			grid[i * offset + j].type = Air;
			x += 10;
		}
		x = 0;
		y += 10;
	}

}

void AtachSandGrain(Block (&grid)[4800], std::shared_ptr<SandGrain> sandGrain) {

	int row = static_cast<int>(sandGrain->rect.y) / 10;
	int column = static_cast<int>(sandGrain->rect.x) / 10;
	int index = (row * 80) + column;
	
	sandGrain->rect = grid[index].rect;
	sandGrain->gridIndex = index;
	grid[index].type = Sand;
	grid[index].sandGrainPointer = sandGrain;
}

void ApplyGravity(Block (&grid)[4800], std::shared_ptr<SandGrain> sandGrain) {

	int offset = 80;
	int random = rand() % 101;

	if (sandGrain == nullptr) return;

	if (sandGrain->gridIndex + offset >= 4800) { // Might have to come here later cause if I add various types and ground can't just be sand.
		grid[sandGrain->gridIndex].type = Sand;
		return;
	}

	if (grid[sandGrain->gridIndex + offset].type == Air) {
		grid[sandGrain->gridIndex].type = Air;
		grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
		sandGrain->rect = grid[sandGrain->gridIndex + offset].rect;
		grid[sandGrain->gridIndex + offset].type = Sand;
		grid[sandGrain->gridIndex + offset].sandGrainPointer = sandGrain;
		sandGrain->gridIndex += offset;
	}

	else if (grid[sandGrain->gridIndex + offset].type == Sand) {
		if (sandGrain->gridIndex % 80 > 0 && grid[sandGrain->gridIndex + offset - 1].type == Air && grid[sandGrain->gridIndex + offset + 1].type == Air) {
			if (random <= 50) {
				grid[sandGrain->gridIndex].type = Air;
				grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
				sandGrain->rect = grid[sandGrain->gridIndex + offset - 1].rect;
				grid[sandGrain->gridIndex + offset - 1].type = Sand;
				grid[sandGrain->gridIndex + offset - 1].sandGrainPointer = sandGrain;
				sandGrain->gridIndex += offset - 1;
				return;
			}
			else if (random > 50) {
				grid[sandGrain->gridIndex].type = Air;
				grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
				sandGrain->rect = grid[sandGrain->gridIndex + offset + 1].rect;
				grid[sandGrain->gridIndex + offset + 1].type = Sand;
				grid[sandGrain->gridIndex + offset + 1].sandGrainPointer = sandGrain;
				sandGrain->gridIndex += offset + 1;
				return;
			}
		}
		else if (grid[sandGrain->gridIndex + offset - 1].type == Air && !grid[sandGrain->gridIndex + offset + 1].type == Air) {
			grid[sandGrain->gridIndex].type = Air;
			grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
			sandGrain->rect = grid[sandGrain->gridIndex + offset - 1].rect;
			grid[sandGrain->gridIndex + offset - 1].type = Sand;
			sandGrain->gridIndex += offset - 1;
			return;
		}

		else if (!grid[sandGrain->gridIndex + offset - 1].type == Air && grid[sandGrain->gridIndex + offset + 1].type == Air) {
			grid[sandGrain->gridIndex].type = Air;
			grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
			sandGrain->rect = grid[sandGrain->gridIndex + offset + 1].rect;
			grid[sandGrain->gridIndex + offset + 1].type = Sand;
			sandGrain->gridIndex += offset + 1;
			return;
		}
	}
	
}
