#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Body.h"

using namespace MATH;

// class for tier 1 & 2 logic

class Item : Body {
public:
	float spawnTime;
	SDL_Rect square;


	Item(){
		spawnTime = 4;
		this->vel.y = -10;
		square.w = 50;
		square.h = 50;
	}

	void SetTexture(SDL_Texture* _texture);
	void SetImage(SDL_Surface* _image);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer, Matrix4 projectionMatrix, float scale);
	bool HasIntersection(SDL_Rect sourceRect);
	void SetPosition(Vec3 position);
	void SetVelocity(Vec3 velocity);
	Vec3 GetPosition();
};

