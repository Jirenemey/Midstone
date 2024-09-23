#include "Scene1.h"
#include <VMath.h>

// See notes about this constructor in Scene1.h.
Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
}

Scene1::~Scene1(){
}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("mouse.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	//game->getPlayer()->setImage(image);
	//game->getPlayer()->setTexture(texture);
	mouse.SetTexture(texture);

	return true;
}

void Scene1::OnDestroy() {
	button.~Button();
	mouse.~Mouse();
}

void Scene1::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);
	mouse.Update();
	button.Update(mouse);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderClear(renderer);

	// render the player
	//game->RenderPlayer(1.0f);
	button.Draw(renderer);
	mouse.Draw(renderer);
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	//game->getPlayer()->HandleEvents(event);
}