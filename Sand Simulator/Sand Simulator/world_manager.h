#pragma once
#include <memory>
#include "sand_grain.h"
#include <SDL3/SDL.h>

const float gravityForce = 9.8f;

Uint64 lastTick = SDL_GetTicks();

/// <summary>
/// Gets time don't think too much about it
/// </summary>
/// <returns>The elapsed time</returns>
float deltaTime() {

	Uint64 currentTick = SDL_GetTicks(); // Example: 5 ---> 6
	Uint64 elapsedTick = currentTick - lastTick; // Example: 5 - 4 ----> 6 - 5 ...
	lastTick = currentTick; // 5

	return static_cast<float>(elapsedTick / 1000.0);
}

void ApplyGravity(std::shared_ptr<SandGrain> sandGrain) { // Check this. Smells like a bug tbh

	float dt = deltaTime();
	sandGrain->velocityY += gravityForce * sandGrain->GetMass() * dt;
	sandGrain->positionY += sandGrain->velocityY * dt;
	sandGrain->rect.y = sandGrain->positionY;
}