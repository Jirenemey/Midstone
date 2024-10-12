#include "Item.h"


void Item::SetTexture(SDL_Texture* _texture) {
	texture = _texture;
}

void Item::SetImage(SDL_Surface* _image){
	image = _image;
}

void Item::Update(float deltaTime) {
	Body::Update(deltaTime);
}

void Item::Draw(SDL_Renderer* renderer, Matrix4 projectionMatrix, float scale) {
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

bool Item::HasIntersection(SDL_Rect sourceRect) {
	return SDL_HasIntersection(&sourceRect, &square);
}

void Item::SetPosition(Vec3 position) {
	this->pos = position;
}

void Item::SetVelocity(Vec3 velocity) {
	this->vel = velocity;
}

Vec3 Item::GetPosition(){
	return this->pos;
}