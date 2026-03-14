#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "utils.h"
#include "rectangle.h"

/// <summary>
/// A sand garin. Takes: Rectangle::(rect, color, *renderer)
/// </summary>
class Material : public Rectangle {

	public:

		float moverTimer = 0;
		int gridIndex = 0;
		Material(SDL_FRect rect, SDL_Color color, SDL_Renderer *renderer) : Rectangle(rect, color, renderer) {}

};
