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
			}
		}

		float x;
		float y;

		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_LMASK) {

			SDL_FRect rect = { x, y, 10, 15 };
			SDL_Color Colors[5] = { { 194, 178, 128, 255 }, { 210, 180, 140, 255 }, { 180, 160, 100, 255 }, { 230, 210, 160, 255 }, { 158, 144, 80, 255 } };

			for (int i = -1; i < 2; i++)
			{
				rect.y += 10 * i;

				int random = rand() % 5;
				auto sandGrain = std::make_shared<SandGrain>(rect, Colors[random], state.renderer);
				AtachSandGrain(Grid, sandGrain);
				sand.push_back(sandGrain);
			}
		}

		if (SDL_GetMouseState(&x, &y) & SDL_BUTTON_RMASK) { // I'll add pointers to the Block struct

			int row = static_cast<int>(y) / 10;
			int column = static_cast<int>(x) / 10;

			for (int i = -3; i < 4; i++)
			{
				for (int j = -3; j < 4; j++)
				{
					int tempRow = row + i;
					int tempColumn = column + j;
					int index = (tempRow * 80) + tempColumn;

					if (tempRow < 0 || tempRow >= 60 || tempColumn < 0 || tempColumn >= 80) continue;

					Grid[index].type = Air;
					auto it = std::find(sand.begin(), sand.end(), Grid[index].sandGrainPointer);
					if (it != sand.end()) sand.erase(it);
					Grid[index].sandGrainPointer = nullptr;
				}
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
