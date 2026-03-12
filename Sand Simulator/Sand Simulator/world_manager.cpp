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
			grid[i * offset + j].isOccupied = false;
			x += 10;
		}
		x = 0;
		y += 10;
	}

}

void AtachSandGrain(Block (&grid)[4800], std::shared_ptr<SandGrain> sandGrain) {

	float offset = 10;

	for (int i = 0; i < 4800; i++)
	{
		if (sandGrain->rect.x >= grid[i].rect.x && sandGrain->rect.x <= grid[i].rect.x + offset
			&& sandGrain->rect.y >= grid[i].rect.y && sandGrain->rect.y <= grid[i].rect.y + offset) {
			sandGrain->rect = grid[i].rect;
			sandGrain->gridIndex = i;
			grid[i].isOccupied = true;
			return;
		}
	}

}

void ApplyGravity(Block (&grid)[4800], std::shared_ptr<SandGrain> sandGrain) {

	int offset = 80;
	
	if (sandGrain->gridIndex + offset >= 4800) {
		grid[sandGrain->gridIndex].isOccupied = true;
		return;
	}
	else if (grid[sandGrain->gridIndex + offset].isOccupied) return;
	else {
		grid[sandGrain->gridIndex].isOccupied = false;
		sandGrain->rect = grid[sandGrain->gridIndex + offset].rect;
		grid[sandGrain->gridIndex + offset].isOccupied = true;
		sandGrain->gridIndex += offset;
	}
}
