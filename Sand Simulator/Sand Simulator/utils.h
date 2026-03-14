#pragma once
#include <iostream>
#include <SDL3/SDL.h>

const int width = 1920;
const int height = 1080;

const int cols = 192;
const int rows = 108;
const int gridSize = cols * rows;
const int cellSize = 10;

const float sandFallingSpeed = 0.0005f;

struct SDL_State {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void _CleanUp(SDL_State& state);
void _InitSDLVideo();
void _InitWindowRenderer(SDL_State& state);