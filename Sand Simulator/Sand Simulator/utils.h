#pragma once
#include <iostream>
#include <SDL3/SDL.h>

const int width = 1080;
const int height = 720;

const int cols = 216;
const int rows = 144;
const int gridSize = cols * rows;
const int cellSize = 5;

struct SDL_State {
	SDL_Window* window;
	SDL_Renderer* renderer;
};

void _CleanUp(SDL_State& state);
void _InitSDLVideo();
void _InitWindowRenderer(SDL_State& state);
void _DisplayFPS(float dt);