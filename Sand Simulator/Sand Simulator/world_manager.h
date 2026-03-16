#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include "material.h"
#include <vector>
#include "utils.h"

enum Type {
	AirType,
	SandType,
	WaterType,
	StoneType,
	FireType
};

struct Block {
	SDL_FRect rect;
	Type type;
	std::shared_ptr<Material> materialPointer;
};

const float gravityForce = 9.8f;

float deltaTime(Uint64& lastTick);

void _AssignBlockRects(Block (&grid)[gridSize]);
void _CreateMaterial(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, SDL_State state, int selectedMaterial);
void _EraseMaterial(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, SDL_State state);
void _AtachMaterial(Block (&grid)[gridSize], std::shared_ptr<Material> material);

void _Render(SDL_State& state, Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, float dt);
void _Update(Block(&grid)[gridSize], std::vector<std::shared_ptr<Material>>& materials, float dt);
