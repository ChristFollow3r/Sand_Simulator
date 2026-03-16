#pragma once
#include <memory>
#include "world_manager.h"

class Stone : public Material {
public:

	static inline SDL_Color Colors[5] = { { 128, 128, 128, 255 }, { 105, 105, 105, 255 }, { 148, 148, 148, 255 }, { 119, 110, 101, 255 }, { 90, 90, 90, 255 } };
	Stone(SDL_FRect rect, SDL_Renderer* renderer) : Material(rect, Colors[rand() % 5], renderer) {};

	void ApplyPhysics(Block(&grid)[gridSize]) override;
};