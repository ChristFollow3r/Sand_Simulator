#pragma once
#include "world_manager.h"
#include <memory>

class SandGrain : public Material {

public: 

	static inline SDL_Color Colors[5] = { { 194, 178, 128, 255 }, { 210, 180, 140, 255 }, { 180, 160, 100, 255 }, { 230, 210, 160, 255 }, { 158, 144, 80, 255 } };

	SandGrain(SDL_FRect rect, SDL_Renderer* renderer) : Material(rect, Colors[rand() % 5], renderer) {
		fallingSpeed = 0.002f;
	};
	void ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions, float dt) override;

};
