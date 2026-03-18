#pragma once
#include <memory>
#include "world_manager.h"

class Water : public Material {

public: 

	// Inline makes the linker pick one array when he finds this line in multiple files instead of making one everytime he encounters this line. This sovles linker issues.
	static inline SDL_Color Colors[5] = { {64, 164, 223, 200}, { 40, 140, 200, 180 }, { 80, 180, 230, 190 }, { 50, 150, 210, 170 }, { 30, 120, 180, 210 } };

	Water(SDL_FRect rect, SDL_Renderer* renderer) : Material(rect, Colors[rand() % 5], renderer) {
		fallingSpeed = 0.0001f;
	};
	void ApplyPhysics(Block* grid) override;

};