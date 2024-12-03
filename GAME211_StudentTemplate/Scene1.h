#ifndef SCENE1_H
#define SCENE1_H

#include <MMath.h>
#include <sstream>
#include <string>
#include <SDL_mixer.h>
#include "Scene.h"
#include "Button.h"
#include "Text.h"
#include "Job.h"
#include "Item.h"
#include "People.h"

using namespace MATH;
class Scene1 : public Scene {
private:
	float xAxis;	// scene width, in game coords, set in constructor
	float yAxis;	// scene height, in game coords, set in constructor
	SDL_Window* window;		// an SDL window with a SDL renderer
	SDL_Renderer* renderer;	// the renderer associated with SDL window
	Matrix4 projectionMatrix;	// set in OnCreate()
	Matrix4     inverseProjection;	// set in OnCreate()
	SDL_Surface* image;
	SDL_Texture* texture;

	Mouse mouse;
	//****************MAIN MENU******************************//
	Button playButton;
	Text titleText = Text("Atop.ttf", 100, "Job Hunt");
	bool play = false;
	SDL_Rect* border;
	SDL_Surface* menuBackground;
	SDL_Texture* menuBackgroundTexture;
	Mix_Music* menuMusic;
	Mix_Chunk* clickSound;

	//***************GAME SCREEN*****************************//
	Job job;
	Text jobInfoText = Text("Atop.ttf", 50, "Job Info");
	Text tierText = Text("Atop.ttf", 40, "Tier: N/A");
	Text wageText = Text("Atop.ttf", 40, "Wage: $0");
	Text searchInfoText = Text("Atop.ttf", 50, "Job Found");
	Text searchTierText = Text("Atop.ttf", 40, "Tier: ");
	Text searchWageText = Text("Atop.ttf", 40, "Wage: ");
	Text walletText = Text("Atop.ttf", 40, "Wallet: $0");
	Text experienceText = Text("Atop.ttf", 40, "Exp: 0");
	SDL_Surface* gameBackground;
	SDL_Texture* gameBackgroundTexture;
	Button applyButton;
	Button searchButton;
	Button startButton;

	//*****************UPGRADE SCREEN**************************//
	Button upgradeScreenButton; // enter upgrade screen
	Button backButton; // exit upgrade screen
	bool upgradeScreen = false;
	// upgrade screen buttons
	Button upgradeWageButton;
	Button upgradeExpButton;
	Button upgradeAccButton;
	// display upgrade info
	Text upgradePrice = Text("Atop.ttf", 40, "Price: ");
	Text upgradeLevel = Text("Atop.ttf", 40, "Level: ");
	Text upgradeDesc = Text("Atop.ttf", 25, "Desc: ");
	float time = 0;
	float bonus = 1;
	int count = 0;

	//*******************JOBS********************************//
	Mix_Chunk* point;

	// Tier1
	Item tier1;
	const char* tier1Assets[4];
	SDL_Surface* tier1Background;
	SDL_Texture* tier1BackgroundTexture;
	Mix_Chunk* tier1Fall;

	//tier 2 variables
	Item tier2[3];
	int tier2Size = sizeof(tier2) / sizeof(tier2[0]);
	const char* tier2Assets[4];
	int tier2Counter = 0;
	int tier2CounterPlayer = 0;
	Button tier2CounterBtn;
	SDL_Surface* tier2Background;
	SDL_Texture* BackgroundTexture2 = SDL_CreateTextureFromSurface(renderer, tier2Background);
	Mix_Chunk* tier2Click;

	//tier 3 variables
	People tier3;
	Mix_Chunk* tier3Steal;
	int tier3Clicks = 10;
	float tier3Time = 2;
	SDL_Surface* tier3Background;
	SDL_Texture* BackgroundTexture3 = SDL_CreateTextureFromSurface(renderer, tier3Background);

	// Tier4
	People tier4[6];
	int tier4Size = sizeof(tier4) / sizeof(tier4[0]);
	float sleepTimer[6];
	Mix_Chunk* tier4Sleep;
	int tier4Clicks = 7;
	SDL_Surface* tier4Background;
	SDL_Texture* BackgroundTexture4;

public:
	// This constructor may be different from what you've seen before
	// Notice the second parameter, and look in GameManager.cpp
	// to see how this constructor is called.
	void StartJob(int tier);
	std::string SetText(const char* text, float num);
	Scene1(SDL_Window* sdlWindow, GameManager* game_);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& event);
	float getxAxis() { return xAxis; }
	float getyAxis() { return yAxis; }
	SDL_Window* getWindow() { return window; }
	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getInverseMatrix() { return inverseProjection; }
};

#endif
