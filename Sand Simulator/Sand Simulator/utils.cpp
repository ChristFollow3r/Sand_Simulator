#include "utils.h"

void _InitSDLVideo() {

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Unable to initialize SDL Video", nullptr);
		exit(1);
	}
}

void _InitWindowRenderer(SDL_State& state) {

	state.window = SDL_CreateWindow("Sand Simulator", width, height, 0);
	state.renderer = SDL_CreateRenderer(state.window, nullptr);

	if (!state.window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Unable to initialize SDL Window", nullptr);
		_CleanUp(state);
		exit(1);
	}

	if (!state.renderer) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "ERROR", "Unable to create the SDL Renderer", nullptr);
		_CleanUp(state);
		exit(1);
	}
}

void _CleanUp(SDL_State& state) {
	SDL_DestroyRenderer(state.renderer);
	SDL_DestroyWindow(state.window);
	SDL_Quit();
}