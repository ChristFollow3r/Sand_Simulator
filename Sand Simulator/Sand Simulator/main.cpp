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

	SDL_State state;
	bool running = true;
	srand(time(NULL));

	Uint64 lastTick = SDL_GetTicks();
	deltaTime(lastTick);

	_InitSDLVideo();
	_InitWindowRenderer(state);

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
		_Render(state, Grid, sand, dt);

	}

	_CleanUp(state);
	return 0;
}


