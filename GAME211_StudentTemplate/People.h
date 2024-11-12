#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Body.h"
class People : Body
	//people class for employees of tier 3 job and suspicious people of tier 4 job
{
public:
	SDL_Rect square;
	int clicks;
	bool asleep;
	float timer;
	float sleepTimer;
	bool sleepImage;

	People() {
		clicks = 0;
		asleep = false;
		timer = 0.0f;
		sleepTimer = 1.0f;
		sleepImage = false;
		square.w = 50;
		square.h = 50;
	};

	void SetTexture(SDL_Texture* _texture);
	void SetImage(SDL_Surface* _image);
	void Update(float deltaTime);
	void Draw(SDL_Renderer* renderer, Matrix4 projectionMatrix, float scale);
	bool HasIntersection(SDL_Rect rect);
	void SetPosition(Vec3 position);
	void ChanceToSleep(float deltaTime);
};

