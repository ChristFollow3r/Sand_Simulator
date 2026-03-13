#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include "utils.h"
#include "sand_grain.h"
#include "rectangle.h"
#include "world_manager.h"
#include <vector>

void cleanUp(SDL_State& state);

int main(int argc, char *argv[]) {

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
	
	float fallingSpeed = 0.01f;
	Block Grid[4800];
	AssignBlockRects(Grid); // Innecessary but it's not a big deal. 
	std::vector<std::shared_ptr<SandGrain>> sand;

	while (running) {

		SDL_Event event{0}; 
		while (SDL_PollEvent(&event)) {

			switch (event.type) {

				case (SDL_EVENT_QUIT):
					running = false;
					break;

				case (SDL_EVENT_MOUSE_BUTTON_DOWN):

					float x;
					float y;
					SDL_GetMouseState(&x, &y);

					SDL_FRect rect = { x, y, 10, 15 };
					SDL_Color color = { 158, 144, 80, 255 };

					auto sandGrain = std::make_shared<SandGrain>(rect, color, state.renderer);
					AtachSandGrain(Grid, sandGrain);
					sand.push_back(sandGrain);
			}
		}	
			
		SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255);
		SDL_RenderClear(state.renderer);
		float dt = deltaTime(lastTick);

		for (auto x : sand) {
			x->DrawRectangle();
			x->moverTimer += dt;
			if (x->moverTimer >= fallingSpeed) {
				ApplyGravity(Grid, x);
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
