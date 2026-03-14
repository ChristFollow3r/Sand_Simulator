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
	std::shared_ptr<Material> sandGrainPointer;
};

const float gravityForce = 9.8f;

float deltaTime(Uint64& lastTick);

void _AssignBlockRects(Block (&grid)[gridSize]);
void _CreateSandGrain(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& sand, SDL_State state);
void _EraseSandGrain(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& sand, SDL_State state);
void _AtachSandGrain(Block (&grid)[gridSize], std::shared_ptr<Material> sandGrain);
void _ApplyGravity(Block(&grid)[gridSize], std::shared_ptr<Material> sandGrain);

void _Render(SDL_State& state, Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& sand, float dt);
void _Update(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& sand, float dt);
