#include <SDL3/SDL.h>
#include <iostream>
#include <memory>
#include "utils.h"
#include "sand_grain.h"
#include "rectangle.h"
#include "world_manager.h"

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

	// Sand grain
	SDL_FRect rect = { 400, 600, 50, 50 };
	SDL_Color color = { 206, 17, 38, 255 };

	//float positionX = rect.x;
	//float positionY = rect.y;

	//auto firstGrain = std::make_shared<SandGrain>(rect, color, state.renderer, positionX, positionY);
	//auto rectangle = std::make_shared<Rectangle>(rect, color, state.renderer);
	// Sand grain


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

		//firstGrain->DrawRectangle();
		//rectangle->DrawRectangle();

		SDL_SetRenderDrawColor(state.renderer, 255, 255, 255, 255); // Picks a color (white)
		SDL_RenderClear(state.renderer); // Paints the screen


		SDL_SetRenderDrawColor(state.renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(state.renderer, &rect);

		//ApplyGravity(deltaTime(), firstGrain);

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
