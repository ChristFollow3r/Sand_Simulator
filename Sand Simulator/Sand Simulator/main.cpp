#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "utils.h"
#include "material.h"
#include "rectangle.h"
#include "world_manager.h"

int main(int argc, char *argv[]) {	

	SDL_State state;

	srand(time(NULL));
	_InitSDLVideo();
	_InitWindowRenderer(state);

	bool running = true;
	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);

	std::vector<std::shared_ptr<Material>> materials;
	Block* Grid = new Block[gridSize];
	_AssignBlockRects(Grid); 

	int selectedMaterial = 0;

	while (running) {

		SDL_Event event{0}; 
		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case (SDL_EVENT_QUIT):
					running = false;
					break;

				case (SDL_EVENT_KEY_DOWN):
					if (event.key.key == SDLK_1) selectedMaterial = 0;
					if (event.key.key == SDLK_2) selectedMaterial = 1;
					if (event.key.key == SDLK_3) selectedMaterial = 2;
					if (event.key.key == SDLK_4) selectedMaterial = 3;
					if (event.key.key == SDLK_5) selectedMaterial = 4;
					if (event.key.key == SDLK_DELETE) {
						while (!materials.empty()) {
							materials.pop_back();
						}
						for (int i = 0; i < gridSize; i++)
						{
							Grid[i].type = AirType;
							Grid[i].materialPointer = nullptr;
						}
					}
					if (event.key.key == SDLK_ESCAPE) exit(0);
					break;
			}
		}

		float dt = deltaTime(lastTick);

		_DisplayFPS(dt);

		_CreateMaterial(Grid, materials, state, selectedMaterial);
		_EraseMaterial(Grid, materials, state);
		_Render(state, Grid, materials, dt);

	}

	_CleanUp(state);
	return 0;
}


