#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "utils.h"
#include "sand_grain.h"
#include "rectangle.h"
#include "world_manager.h"
#include "utils.h"

int main(int argc, char *argv[]) {

	srand(time(NULL));
	SDL_State state;


	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);

	_InitSDLVideo();
	_InitWindowRenderer(state);

	bool running = true;

	
	std::vector<std::shared_ptr<SandGrain>> sand;
	Block Grid[gridSize];
	_AssignBlockRects(Grid); 

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

	_CleanUp(state);
	return 0;
}


