#pragma once
#include <SDL3/SDL.h>

Uint64 lastTick = SDL_GetTicks(); // Example: 4

/// <summary>
/// Gets time don't think too much about it
/// </summary>
/// <returns>The elapsed time</returns>
Uint64 deltaTime() {

	Uint64 currentTick = SDL_GetTicks(); // Example: 5 ---> 6
	Uint64 elapsedTick = currentTick - lastTick; // Example: 5 - 4 ----> 6 - 5 ...
	Uint64 lasTick = currentTick; // 5

	return elapsedTick / 1000.0;
}