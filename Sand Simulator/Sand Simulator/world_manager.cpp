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

void _CreateSandGrain(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, SDL_State state) {

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
				auto sandGrain = std::make_shared<Material>(rect, Colors[random], state.renderer);
				_AtachMaterial(grid, sandGrain);
				materials.push_back(sandGrain);

			}
		}
	}
}

void _EraseMaterial(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, SDL_State state) {

	float x;
	float y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_RMASK) {

		x = std::clamp(x, 0.0f, (float)(width - 1));
		y = std::clamp(y, 0.0f, (float)(height - 1));

		int row = static_cast<int>(y) / 10;
		int column = static_cast<int>(x) / 10;

		for (int i = -3; i < 4; i++)
		{
			for (int j = -3; j < 4; j++)
			{
				int tempRow = row + i;
				int tempColumn = column + j;
				int index = (tempRow * cols) + tempColumn;

				if (tempRow < 0 || tempRow >= rows || tempColumn < 0 || tempColumn >= cols) continue;

				grid[index].type = Air;
				auto it = std::find(materials.begin(), materials.end(), grid[index].materialPointer);
				if (it != materials.end()) materials.erase(it);
				grid[index].materialPointer = nullptr;
			}
		}
	}
}

void _AtachMaterial(Block (&grid)[gridSize], std::shared_ptr<Material> material) {

	int row = static_cast<int>(material->rect.y) / 10;
	int column = static_cast<int>(material->rect.x) / 10;
	int index = (row * cols) + column;
	
	material->rect = grid[index].rect;
	material->gridIndex = index;
	grid[index].type = Sand;
	grid[index].materialPointer = material;
}

void _ApplyGravity(Block (&grid)[gridSize], std::shared_ptr<Material> material) {

	int random = rand() % 101;
	//int boundry = sandGrain->gridIndex % 80;

	if (material == nullptr) return;

	if (material->gridIndex + cols >= gridSize) { // Might have to come here later cause if I add various types and ground can't just be sand.
		grid[material->gridIndex].type = Sand;
		grid[material->gridIndex].materialPointer = material;
		return;
	}

	if (grid[material->gridIndex + cols].type == Air) {
		grid[material->gridIndex].type = Air;
		grid[material->gridIndex].materialPointer = nullptr;
		material->rect = grid[material->gridIndex + cols].rect;
		grid[material->gridIndex + cols].type = Sand;
		grid[material->gridIndex + cols].materialPointer = material;
		material->gridIndex += cols;
	}

	else if (grid[material->gridIndex + cols].type == Sand) {
		if (grid[material->gridIndex + cols - 1].type == Air && grid[material->gridIndex + cols + 1].type == Air) {
			if (random <= 50) {
				grid[material->gridIndex].type = Air;
				grid[material->gridIndex].materialPointer = nullptr;
				material->rect = grid[material->gridIndex + cols - 1].rect;
				grid[material->gridIndex + cols - 1].type = Sand;
				grid[material->gridIndex + cols - 1].materialPointer = material;
				material->gridIndex += cols - 1;
				return;
			}
			else if (random > 50) {
				grid[material->gridIndex].type = Air;
				grid[material->gridIndex].materialPointer = nullptr;
				material->rect = grid[material->gridIndex + cols + 1].rect;
				grid[material->gridIndex + cols + 1].type = Sand;
				grid[material->gridIndex + cols + 1].materialPointer = material;
				material->gridIndex += cols + 1;
				return;
			}
		}
		else if (grid[material->gridIndex + cols - 1].type == Air && !grid[material->gridIndex + cols + 1].type == Air) {
			grid[material->gridIndex].type = Air;
			grid[material->gridIndex].materialPointer = nullptr;
			material->rect = grid[material->gridIndex + cols - 1].rect;
			grid[material->gridIndex + cols - 1].type = Sand;
			material->gridIndex += cols - 1;
			return;
		}

		else if (!grid[material->gridIndex + cols - 1].type == Air && grid[material->gridIndex + cols + 1].type == Air) {
			grid[material->gridIndex].type = Air;
			grid[material->gridIndex].materialPointer = nullptr;
			material->rect = grid[material->gridIndex + cols + 1].rect;
			grid[material->gridIndex + cols + 1].type = Sand;
			material->gridIndex += cols + 1;
			return;
		}
	}
	
}

void _Render(SDL_State& state, Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, float dt) {
	SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
	SDL_RenderClear(state.renderer);
	_Update(grid, materials, dt);
	SDL_RenderPresent(state.renderer);
}

void _Update(Block (&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, float dt) {
	for (auto x : materials) {
		x->DrawRectangle();
		x->moverTimer += dt;
		if (x->moverTimer >= sandFallingSpeed) {
			_ApplyGravity(grid, x);
			x->moverTimer = 0;
		}
	}
}