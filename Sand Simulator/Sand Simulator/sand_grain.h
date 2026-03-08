#pragma once
#include <SDL3/SDL.h>
#include <iostream>
#include "utils.h"
#include "rectangle.h"

/// <summary>
/// A sand garin. Takes: Rectangle::(rect, color, *renderer), currentPosition, lastPosition, mass
/// </summary>
class SandGrain : public Rectangle {

	public:

		float velocityY = 0;
		float positionX = 0;
		float positionY = 0;

		SandGrain(SDL_FRect rect, SDL_Color color, SDL_Renderer *renderer, float positionX, float positionY) 
			: Rectangle(rect, color, renderer), positionX(positionX), positionY(positionY) {}

		float GetMass() { return this->mass; };

		// To do: Fill the sand grains here instead of in main

	private:

		const float mass = 0.07;
};