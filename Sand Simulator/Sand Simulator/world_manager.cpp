#include "world_manager.h"
#include <algorithm>
#include <vector>

float deltaTime(Uint64& lastTick) {

	Uint64 currentTick = SDL_GetTicks(); // Example: 5 ---> 6
	Uint64 elapsedTick = currentTick - lastTick; // Example: 5 - 4 ----> 6 - 5 ...
	lastTick = currentTick; // 5

	return static_cast<float>(elapsedTick / 1000.0);
}

void _AssignBlockRects(Block(&grid)[gridSize]) {

	float x = 0;
	float y = 0;
	float height = 10;
	float width = 10;


	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			SDL_FRect newRect = { x, y, height, width };
			grid[i * cols + j].rect = newRect;
			grid[i * cols + j].type = Air;
			x += 10;
		}
		x = 0;
		y += 10;
	}

}

void _CreateSandGrain(Block(&grid)[gridSize], std::vector<std::shared_ptr<SandGrain>>& sand, SDL_State state) {

	float x;
	float y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_LMASK) {

		x = std::clamp(x, 0.0f, (float)(width - 1));
		y = std::clamp(y, 0.0f, (float)(height - 1));

		SDL_Color Colors[5] = { { 194, 178, 128, 255 }, { 210, 180, 140, 255 }, { 180, 160, 100, 255 }, { 230, 210, 160, 255 }, { 158, 144, 80, 255 } };

		for (int i = -1; i < 1; i++)
		{
			for (int j = -1; j < 1; j++) {

				float spawnX = x + i * 10.0f;
				float spawnY = y + j * 10.0f;
				if (spawnX < 0.0f || spawnX >= width || spawnY < 0.0f || spawnY >= height) continue;

				SDL_FRect rect = { spawnX, spawnY, 10, 15 };
				int random = rand() % 5;
				auto sandGrain = std::make_shared<SandGrain>(rect, Colors[random], state.renderer);
				_AtachSandGrain(grid, sandGrain);
				sand.push_back(sandGrain);

			}
		}
	}
}

void _AtachSandGrain(Block (&grid)[gridSize], std::shared_ptr<SandGrain> sandGrain) {

	int row = static_cast<int>(sandGrain->rect.y) / 10;
	int column = static_cast<int>(sandGrain->rect.x) / 10;
	int index = (row * cols) + column;
	
	sandGrain->rect = grid[index].rect;
	sandGrain->gridIndex = index;
	grid[index].type = Sand;
	grid[index].sandGrainPointer = sandGrain;
}

void _ApplyGravity(Block (&grid)[gridSize], std::shared_ptr<SandGrain> sandGrain) {

	int random = rand() % 101;
	//int boundry = sandGrain->gridIndex % 80;

	if (sandGrain == nullptr) return;

	if (sandGrain->gridIndex + cols >= gridSize) { // Might have to come here later cause if I add various types and ground can't just be sand.
		grid[sandGrain->gridIndex].type = Sand;
		grid[sandGrain->gridIndex].sandGrainPointer = sandGrain;
		return;
	}

	if (grid[sandGrain->gridIndex + cols].type == Air) {
		grid[sandGrain->gridIndex].type = Air;
		grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
		sandGrain->rect = grid[sandGrain->gridIndex + cols].rect;
		grid[sandGrain->gridIndex + cols].type = Sand;
		grid[sandGrain->gridIndex + cols].sandGrainPointer = sandGrain;
		sandGrain->gridIndex += cols;
	}

	else if (grid[sandGrain->gridIndex + cols].type == Sand) {
		if (grid[sandGrain->gridIndex + cols - 1].type == Air && grid[sandGrain->gridIndex + cols + 1].type == Air) {
			if (random <= 50) {
				grid[sandGrain->gridIndex].type = Air;
				grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
				sandGrain->rect = grid[sandGrain->gridIndex + cols - 1].rect;
				grid[sandGrain->gridIndex + cols - 1].type = Sand;
				grid[sandGrain->gridIndex + cols - 1].sandGrainPointer = sandGrain;
				sandGrain->gridIndex += cols - 1;
				return;
			}
			else if (random > 50) {
				grid[sandGrain->gridIndex].type = Air;
				grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
				sandGrain->rect = grid[sandGrain->gridIndex + cols + 1].rect;
				grid[sandGrain->gridIndex + cols + 1].type = Sand;
				grid[sandGrain->gridIndex + cols + 1].sandGrainPointer = sandGrain;
				sandGrain->gridIndex += cols + 1;
				return;
			}
		}
		else if (grid[sandGrain->gridIndex + cols - 1].type == Air && !grid[sandGrain->gridIndex + cols + 1].type == Air) {
			grid[sandGrain->gridIndex].type = Air;
			grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
			sandGrain->rect = grid[sandGrain->gridIndex + cols - 1].rect;
			grid[sandGrain->gridIndex + cols - 1].type = Sand;
			sandGrain->gridIndex += cols - 1;
			return;
		}

		else if (!grid[sandGrain->gridIndex + cols - 1].type == Air && grid[sandGrain->gridIndex + cols + 1].type == Air) {
			grid[sandGrain->gridIndex].type = Air;
			grid[sandGrain->gridIndex].sandGrainPointer = nullptr;
			sandGrain->rect = grid[sandGrain->gridIndex + cols + 1].rect;
			grid[sandGrain->gridIndex + cols + 1].type = Sand;
			sandGrain->gridIndex += cols + 1;
			return;
		}
	}
	
}
