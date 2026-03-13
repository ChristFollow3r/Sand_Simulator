#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "sand_grain.h"
#include <vector>
#include "utils.h"

enum Type {
	Air,
	Sand,
	Water,
	Stone,
	Fire
};

struct Block {
	SDL_FRect rect;
	Type type;
	std::shared_ptr<SandGrain> sandGrainPointer;
};

const float gravityForce = 9.8f;

float deltaTime(Uint64& lastTick);

void AssignBlockRects(Block (&grid)[gridSize]);
void AtachSandGrain(Block (&grid)[gridSize], std::shared_ptr<SandGrain> sandGrain);
void ApplyGravity(Block(&grid)[gridSize], std::shared_ptr<SandGrain> sandGrain);



