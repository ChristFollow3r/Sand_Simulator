#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include "mainF.h"
#include "rectangle.h"

void cleanUp(SDL_State& state);

int main(int argc, char *argv[]) {

	SDL_State state;
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

	while (running) {

		SDL_Event event{0}; 
		while (SDL_PollEvent(&event)) {

			switch (event.type) {
				case (SDL_EVENT_QUIT):
					running = false;
					break;
			}
		}	

		// Drawing commands
		SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255); // Picks a color (white)
		SDL_RenderClear(state.renderer); // Paints the screen
		// Swap buffer and pressent
		SDL_RenderPresent(state.renderer); // Presents the new painted screen
	}

	cleanUp(state);
	return 0;
}

void cleanUp(SDL_State& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}