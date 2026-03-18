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
	DirtType,
	FireType
};

struct Block {
	SDL_FRect rect;
	Type type;
	std::shared_ptr<Material> materialPointer;
};

const float gravityForce = 9.8f;

float deltaTime(Uint64& lastTick);

void _AssignBlockRects(Block* grid);
void _CreateMaterial(Block* grid, std::vector<std::shared_ptr<Material>>& materials, SDL_State state, int selectedMaterial);
void _EraseMaterial(Block* grid, std::vector<std::shared_ptr<Material>>& materials, SDL_State state);
void _AtachMaterial(Block* grid, std::shared_ptr<Material> material, Type materialType);

void _Render(SDL_State& state, Block* grid, std::vector<std::shared_ptr<Material>>& materials, float dt);
void _Update(Block* grid, std::vector<std::shared_ptr<Material>>& materials, float dt);
