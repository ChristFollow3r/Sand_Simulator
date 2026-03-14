#include "world_manager.h"
#include "sandGrain.h"
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

void _CreateMaterial(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, SDL_State state) {

	float x;
	float y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_LMASK) {

		x = std::clamp(x, 0.0f, (float)(width - 1));
		y = std::clamp(y, 0.0f, (float)(height - 1));

		for (int i = -1; i < 1; i++)
		{
			for (int j = -1; j < 1; j++) {

				float spawnX = x + i * 10.0f;
				float spawnY = y + j * 10.0f;
				if (spawnX < 0.0f || spawnX >= width || spawnY < 0.0f || spawnY >= height) continue;

				SDL_FRect rect = { spawnX, spawnY, 10, 15 };
				int random = rand() % 5;
				auto sandGrain = std::make_shared<SandGrain>(rect, state.renderer);
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
			x->ApplyPhysics(grid);
			x->moverTimer = 0;
		}
	}
}