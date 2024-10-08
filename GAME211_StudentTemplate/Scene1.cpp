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
	startButton.sourceRect.y = 500;
	startButton.destinationRect.x = w/2 - startButton.sourceRect.w/2;
	startButton.destinationRect.y = h/2 - startButton.sourceRect.h/2;
	startButton.SetTexture(renderer, "buttons2.png");

	applyButton.sourceRect.y = 100;
	applyButton.destinationRect.x = w - w/3;
	applyButton.destinationRect.y = h - h/4;
	applyButton.SetTexture(renderer, "buttons2.png");

	searchButton.sourceRect.y = 400;
	searchButton.destinationRect.x = w - w/3;
	searchButton.destinationRect.y = h - (h * 3/7);
	searchButton.SetTexture(renderer, "buttons2.png");

	titleText.x = w/4;
	titleText.y = h/12;
	border = new SDL_Rect();
	border->w = w - w/15;
	border->h = h - h/15;
	border->x = w/2 - border->w/2;
	border->y = h/2 - border->h/2;

	return true;
}

void Scene1::OnDestroy() {
	startButton.~Button();
	mouse.~Mouse();
	titleText.~Text();
}

void Scene1::Update(const float deltaTime) {

	// Update player
	game->getPlayer()->Update(deltaTime);
	mouse.Update();
	startButton.Update(mouse);
	applyButton.Update(mouse);
	searchButton.Update(mouse);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// render the player
	//game->RenderPlayer(1.0f);
	if (!start) {
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderFillRect(renderer, border);
		startButton.Draw(renderer);
		titleText.Draw(renderer);
	}else {
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderClear(renderer);
		searchButton.Draw(renderer);
		applyButton.Draw(renderer);
	}
	mouse.Draw(renderer);
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	//game->getPlayer()->HandleEvents(event);
	switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (startButton.isSelected) {
					std::cout << "Start button clicked" << std::endl;
					start = true;
				}
				if (searchButton.isSelected) {
					std::cout << "Search button clicked" << std::endl;
					job.Search();
				}
				if (applyButton.isSelected) {
					std::cout << "Apply button clicked" << std::endl;
					job.Apply();
				}
			}
	}

}
