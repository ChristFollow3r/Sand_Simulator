#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "utils.h"
#include "rectangle.h"

struct Block;

/// <summary>
/// A sand garin. Takes: Rectangle::(rect, color, *renderer)
/// </summary>
class Material : public Rectangle, public std::enable_shared_from_this<Material> {

	public:

		float fallingSpeed = 0;
		float moverTimer = 0;
		int gridIndex = 0;

		Material(SDL_FRect rect, SDL_Color color, SDL_Renderer *renderer) : Rectangle(rect, color, renderer) {}

		virtual void ApplyPhysics(Block* grid, std::vector<std::shared_ptr<Material>>& additions, float dt) = 0;

};
