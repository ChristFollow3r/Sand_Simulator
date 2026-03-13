#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "utils.h"
#include "sand_grain.h"
#include "rectangle.h"
#include "world_manager.h"

void cleanUp(SDL_State& state);

int main(int argc, char *argv[]) {

	srand(time(NULL));
	SDL_State state;
	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);
	bool running = true;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Unable to initialize SDL Video", nullptr);
		return 1;
	}

	state.window = SDL_CreateWindow("Sand Simulator", width, height, 0);
	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Unable to initialize SDL Window", nullptr);
		cleanUp(state);
		return 1;
	}

	state.renderer = SDL_CreateRenderer(state.window, nullptr);
	if (!state.renderer) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Unable to create the SDL Renderer", nullptr);
		cleanUp(state);
		return 1;
	}
	
	Block Grid[gridSize];
	_AssignBlockRects(Grid); // Innecessary but it's not a big deal. 
	std::vector<std::shared_ptr<SandGrain>> sand;

	while (running) {

		SDL_Event event{0}; 
		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case (SDL_EVENT_QUIT):
					running = false;
					break;
			}
		}

		float x;
		float y;

		_CreateSandGrain(Grid, sand, state);

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

					Grid[index].type = Air;
					auto it = std::find(sand.begin(), sand.end(), Grid[index].sandGrainPointer);
					if (it != sand.end()) sand.erase(it);
					Grid[index].sandGrainPointer = nullptr;
				}
			}
		}


			
		SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
		SDL_RenderClear(state.renderer);
		float dt = deltaTime(lastTick);

		for (auto x : sand) {
			x->DrawRectangle();
			x->moverTimer += dt;
			if (x->moverTimer >= sandFallingSpeed) {
				_ApplyGravity(Grid, x);
				x->moverTimer = 0;
			}
		}
		SDL_RenderPresent(state.renderer); 
	}

	cleanUp(state);
	return 0;
}

void cleanUp(SDL_State& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}
