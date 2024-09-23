#include "Mouse.h"

Mouse::Mouse() {
	texture = NULL;
	rect.w = 25;
	rect.h = 25;
	point.w = 1;
	point.h = 1;
	SDL_ShowCursor(false);
}

Mouse::~Mouse() {
	delete texture;
}

void Mouse::SetTexture(SDL_Renderer* renderer, const char* file) {
	texture = IMG_LoadTexture(renderer, file);
}

void Mouse::SetTexture(SDL_Texture* texture_) {
	texture = texture_;
}

void Mouse::Update() {
	SDL_GetMouseState(&rect.x, &rect.y);
	point.x = rect.x;
	point.y = rect.y;
}

void Mouse::Draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}