#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "sand_grain.h"
#include <vector>
#include "utils.h"

struct Block {
	SDL_FRect rect;
	bool isOccupied;
};

const float gravityForce = 9.8f;

void AssignBlockRects(Block (&grid)[4800]);
void AtachSandGrain(Block (&grid)[4800], std::shared_ptr<SandGrain> sandGrain);

float deltaTime(Uint64& lastTick);

void ApplyGravity(Block(&grid)[4800], std::shared_ptr<SandGrain> sandGrain);

