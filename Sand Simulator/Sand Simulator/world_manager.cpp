#include "world_manager.h"

float deltaTime(Uint64& lastTick) {

	Uint64 currentTick = SDL_GetTicks(); // Example: 5 ---> 6
	Uint64 elapsedTick = currentTick - lastTick; // Example: 5 - 4 ----> 6 - 5 ...
	lastTick = currentTick; // 5

	return static_cast<float>(elapsedTick / 1000.0);
}

void ApplyGravity(std::shared_ptr<SandGrain> sandGrain, float dt) {
	sandGrain->velocityY += gravityForce * sandGrain->GetMass() * dt;
	sandGrain->rect.y += sandGrain->velocityY * dt;
	CheckCollisions(sandGrain);
}

void CheckCollisions(std::shared_ptr<SandGrain> sandGrain) {
	if (sandGrain->rect.y > 585) sandGrain->rect.y = 585;
}