#include "Button.h"

Button::Button() {
	texture = NULL;

	sourceRect.h = 100;
	sourceRect.w = 400;
	sourceRect.x = 0;
	
	destinationRect.h = 75;
	destinationRect.w = 300;
}

Button::~Button() {
	delete texture;
}

void Button::SetTexture(SDL_Renderer* renderer, const char* file) {
	texture = IMG_LoadTexture(renderer, file);
}

void Button::SetTexture(SDL_Texture* texture_) {
	texture = texture_;
}

void Button::Update(Mouse &mouse) {
	if (SDL_HasIntersection(&mouse.rect, &destinationRect)) {
		isSelected = true;
		sourceRect.x = 400;
	}
	else {
		isSelected = false;
		sourceRect.x = 0;
	}
}

void Button::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &sourceRect, &destinationRect);
}