#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Mouse{
public:
	SDL_Texture* texture;
	SDL_Rect rect, point;

	Mouse();
	void SetTexture(SDL_Renderer* renderer, const char* file);
	void SetTexture(SDL_Texture* texture_);
	virtual ~Mouse();
	void Update();
	void Draw(SDL_Renderer*);
};

