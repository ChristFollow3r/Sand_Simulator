#pragma once
#include <SDL3/SDL.h>

/// <summary>
/// The base rectangle class (rect, color, renderer).
/// </summary>
class Rectangle {

	public: 

		SDL_FRect rect;
		SDL_Color color;

		Rectangle(SDL_FRect rect, SDL_Color color, SDL_Renderer *renderer)
			: rect(rect), color(color), renderer(renderer) {};

		void DrawRectangle();

	protected:

		SDL_Renderer *renderer;
		
};