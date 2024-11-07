#ifndef SCENE1_H
#define SCENE1_H

#include <MMath.h>
#include "Scene.h"
#include "Button.h"
#include "Text.h"
#include "Job.h"
#include "Item.h"

using namespace MATH;
class Scene1 : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
    Matrix4 inverseProjection;	// set in OnCreate()
	Mouse mouse;
	Button playButton;
	Text titleText = Text("Atop.ttf", 100, "Job Hunt");

	Job job;
	Text tierText = Text("Atop.ttf", 50, "Tier: ");
	Text wageText = Text("Atop.ttf", 50, "Wage: ");
	Button applyButton;
	Button searchButton;
	Button startButton;
	bool play = false;

	float time = 0;

	Item tier1;

	float bonus = 1;
	int count = 0;

	SDL_Rect* border;

	SDL_Surface* tier1Background;
	SDL_Texture* BackgroundTexture = SDL_CreateTextureFromSurface(renderer, tier1Background);

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	void StartJob(int tier);
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
    void HandleEvents(const SDL_Event &event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
    Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};

#endif
