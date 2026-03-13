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
	_AssignBlockRects(Grid); 
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

		float dt = deltaTime(lastTick);

		_CreateSandGrain(Grid, sand, state);
		_EraseSandGrain(Grid, sand, state);
			
		SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
		SDL_RenderClear(state.renderer);

		_Update(Grid, sand, dt);

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
