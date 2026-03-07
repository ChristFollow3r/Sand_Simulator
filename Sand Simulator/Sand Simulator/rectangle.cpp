#include "rectangle.h"

void Rectangle::DrawRectangle() {
	SDL_RenderRect(this->renderer, &this->rect);
	SDL_SetRenderDrawColor(this->renderer, this->color.r, this->color.g, this->color.b, this->color.a);
	SDL_RenderFillRect(this->renderer, &this->rect);
}
	