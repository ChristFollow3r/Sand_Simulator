#pragma once
#include "material.h"
#include "world_manager.h"

class Seed : public Material {
public:

	bool hasGrown = false;
	int maxGrowth = rand() % 4;
	float growthRate = rand() % 60;

	static inline SDL_Color Colors[3] = { {92, 61, 30, 255}, {139, 99, 64, 255}, {58, 32, 16, 255} };
	Seed(SDL_FRect rect, SDL_Renderer* renderer) : Material(rect, Colors[rand() % 3], renderer) {
		fallingSpeed = 0.002f;
	};

	void ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions, float dt) override;
};