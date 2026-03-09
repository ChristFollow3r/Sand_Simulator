#pragma once
#include <iostream>
#include <SDL3/SDL.h>

const int width = 800;
const int height = 600;

struct SDL_State {
	SDL_Window* window;
	SDL_Renderer* renderer;
};
