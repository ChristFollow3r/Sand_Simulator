#include "world_manager.h"
#include "sandGrain.h"
#include "water.h"
#include "stone.h"
#include "dirt.h"
#include "seed.h"
#include <algorithm>
#include <vector>

float deltaTime(Uint64& lastTick) {

	Uint64 currentTick = SDL_GetTicks(); // Example: 5 ---> 6
	Uint64 elapsedTick = currentTick - lastTick; // Example: 5 - 4 ----> 6 - 5 ...
	lastTick = currentTick; // 5

	return static_cast<float>(elapsedTick / 1000.0);
}

void _AssignBlockRects(Block* grid) {

	float x = 0;
	float y = 0;
	float height = 5;
	float width = 5;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			SDL_FRect newRect = { x, y, height, width };
			grid[i * cols + j].rect = newRect;
			grid[i * cols + j].type = AirType;
			x += 5;
		}
		x = 0;
		y += 5;
	}

}

void _CreateMaterial(Block* grid, std::vector<std::shared_ptr<Material>>& materials, SDL_State state, int selectedMaterial) {

	float x;
	float y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_LMASK) {

		x = std::clamp(x, 0.0f, (float)(width - 1));
		y = std::clamp(y, 0.0f, (float)(height - 1));
		Type currentType;

		for (int i = -1; i < 1; i++)
		{
			for (int j = -1; j < 1; j++) {

				float spawnX = x + i * 5.0f;
				float spawnY = y + j * 5.0f;

				if (spawnX < 0.0f || spawnX >= width || spawnY < 0.0f || spawnY >= height) continue;
				SDL_FRect rect = { spawnX, spawnY, 5, 5 };
				std::shared_ptr<Material> material;

				switch (selectedMaterial) {
				case 0:
					material = std::make_shared<SandGrain>(rect, state.renderer);
					currentType = SandType;
					break;
				case 1:
					material = std::make_shared<Water>(rect, state.renderer);
					currentType = WaterType;
					break;
				case 2:
					material = std::make_shared<Stone>(rect, state.renderer);
					currentType = StoneType;
					break;
				case 3:
					material = std::make_shared<Dirt>(rect, state.renderer);
					currentType = DirtType;
					break;
				case 4:
					material = std::make_shared<Seed>(rect, state.renderer);
					currentType = SeedType;
					break;
				}
				
				_AtachMaterial(grid, material, currentType);
				materials.push_back(material);

			}
		}
	}
}

void _EraseMaterial(Block* grid, std::vector<std::shared_ptr<Material>>& materials, SDL_State state) {

	float x;
	float y;

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_RMASK) {

		x = std::clamp(x, 0.0f, (float)(width - 1));
		y = std::clamp(y, 0.0f, (float)(height - 1));

		int row = static_cast<int>(y) / 5;
		int column = static_cast<int>(x) / 5;

		for (int i = -3; i < 4; i++)
		{
			for (int j = -3; j < 4; j++)
			{
				int tempRow = row + i;
				int tempColumn = column + j;
				int index = (tempRow * cols) + tempColumn;

				if (tempRow < 0 || tempRow >= rows || tempColumn < 0 || tempColumn >= cols) continue;

				grid[index].type = AirType;
				auto it = std::find(materials.begin(), materials.end(), grid[index].materialPointer);
				if (it != materials.end()) materials.erase(it);
				grid[index].materialPointer = nullptr;
			}
		}
	}
}

void _AtachMaterial(Block* grid, std::shared_ptr<Material> material, Type materialType) {
	int row = static_cast<int>(material->rect.y) / 5;
	int column = static_cast<int>(material->rect.x) / 5;
	int index = (row * cols) + column;
	
	material->rect = grid[index].rect;
	material->gridIndex = index;
	grid[index].type = materialType;
	grid[index].materialPointer = material;
}

void _Render(SDL_State& state, Block* grid, std::vector<std::shared_ptr<Material>>& materials, float dt) {
	SDL_SetRenderDrawColor(state.renderer, 0, 0, 0, 255);
	SDL_RenderClear(state.renderer);
	_Update(grid, materials, dt);
	SDL_RenderPresent(state.renderer);
}

void _Update(Block* grid, std::vector<std::shared_ptr<Material>>& materials, float dt) {
	materials.reserve(materials.size() + 30000);
	for (auto x : materials) {
		x->DrawRectangle();
		x->moverTimer += dt;
		if (x->moverTimer >= x->fallingSpeed) {
			x->ApplyPhysics(grid);
			x->moverTimer = 0;
		}
	}
}