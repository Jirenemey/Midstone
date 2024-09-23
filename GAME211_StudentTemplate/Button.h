#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Mouse.h"

class Button {
public:
	SDL_Texture* texture;
	SDL_Rect sourceRect, destinationRect;
	bool isSelected = false;

	Button();
	virtual ~Button();

	void SetTexture(SDL_Renderer* renderer, const char* file);
	void SetTexture(SDL_Texture* texture_);

	void Update(Mouse& mouse);
	void Draw(SDL_Renderer* renderer);

};

