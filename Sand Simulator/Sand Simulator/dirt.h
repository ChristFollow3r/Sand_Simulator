#pragma once
#include "material.h"
#include "world_manager.h"

class Dirt : public Material {

public:

	static inline SDL_Color Colors[5] = { { 101, 67, 33, 255 }, { 121, 85, 45, 255 }, { 139, 90, 43, 255 }, { 85, 55, 25, 255 }, { 115, 80, 40, 255 } };
	Dirt(SDL_FRect rect, SDL_Renderer* renderer) : Material(rect, Colors[rand() % 5], renderer) {
		fallingSpeed = 0.0002;
	};
	void ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions) override;
};