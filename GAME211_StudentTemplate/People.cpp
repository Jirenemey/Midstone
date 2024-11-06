#include "People.h"

void People::SetTexture(SDL_Texture* _texture)
{
	texture = _texture;
}

void People::SetImage(SDL_Surface* _image)
{
	image = _image;
}

void People::Update(float deltaTime)
{
	Body::Update(deltaTime);
	ChanceToSleep(deltaTime);
}


void People::Draw(SDL_Renderer* renderer, Matrix4 projectionMatrix, float scale)
{
		//taken from playerbody.cpp
		Vec3 screenCoords;
		float w, h;

		screenCoords = projectionMatrix * pos;

		w = image->w * scale;
		h = image->h * scale;

		square.x = static_cast<int>(screenCoords.x - 0.5f * w);
		square.y = static_cast<int>(screenCoords.y - 0.5f * h);
		square.w = static_cast<int>(w);
		square.h = static_cast<int>(h);

		// Convert character orientation from radians to degrees.
		float orientationDegrees = orientation * 180.0f / M_PI;

		SDL_RenderCopyEx(renderer, texture, nullptr, &square,
			orientationDegrees, nullptr, SDL_FLIP_NONE);
}

bool People::HasIntersection(SDL_Rect sourceRect) {
	return SDL_HasIntersection(&sourceRect, &square);
}

void People::SetPosition(Vec3 position){
	this->pos = position;
}

void People::ChanceToSleep(float deltaTime)
{
	timer += deltaTime;
	if (timer >= sleepTimer && !asleep) {
		int x = rand() % 100 + 1;
		std::cout << x << std::endl;
		timer = 0;
		if (x < 10){
			asleep = true;
		}
	}
}