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

	//setting all buttons with images and location on screen
	image = IMG_Load("mouse.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	mouse.SetTexture(texture);
	playButton.sourceRect.y = 500;
	playButton.destinationRect.x = w/2 - playButton.sourceRect.w/2;
	playButton.destinationRect.y = h/2 - playButton.sourceRect.h/2;
	playButton.SetTexture(renderer, "buttons2.png");

	applyButton.sourceRect.y = 100;
	applyButton.destinationRect.x = w - w/3;
	applyButton.destinationRect.y = h - h/4;
	applyButton.SetTexture(renderer, "buttons2.png");

	searchButton.sourceRect.y = 400;
	searchButton.destinationRect.x = w - w/3;
	searchButton.destinationRect.y = h - (h * 3/7);
	searchButton.SetTexture(renderer, "buttons2.png");

	startButton.sourceRect.y = 000;
	startButton.destinationRect.x = w - (w * 4 / 5);
	startButton.destinationRect.y = h - h / 4;
	startButton.SetTexture(renderer, "buttons2.png");

	titleText.x = w/4;
	titleText.y = h/12;

	tierText.y = h / 12;
	border = new SDL_Rect();
	border->w = w - w/15;
	border->h = h - h/15;
	border->x = w/2 - border->w/2;
	border->y = h/2 - border->h/2;

	image = IMG_Load("Pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);
	tier1.SetImage(image);
	tier1.SetTexture(texture);
	tier1.SetPosition(Vec3(10, 10, 0));

	game->getPlayer()->setPos(Vec3(10, 1, 0));


	return true;
}

void Scene1::OnDestroy() {
	playButton.~Button();
	mouse.~Mouse();
	titleText.~Text();
}

void Scene1::Update(const float deltaTime) {
	// Update player
	game->getPlayer()->Update(deltaTime);
	mouse.Update();
	playButton.Update(mouse);
	applyButton.Update(mouse);
	searchButton.Update(mouse);
	startButton.Update(mouse);
	tier1.Update(deltaTime);

	if (job.startJob == true) {
		if (job.tier == 1) {
			time += deltaTime;
			if (time >= tier1.spawnTime) {
				time = 0;
			}
		}
	}
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// render the player
	if (!play) {
		SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
		SDL_RenderFillRect(renderer, border);
		playButton.Draw(renderer);
		titleText.Draw(renderer);
	}
	else {
		if (job.startJob) {
			StartJob(job.tier);
			game->getPlayer()->Render(0.10f);
		}
		else {
			SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
			SDL_RenderClear(renderer);
			searchButton.Draw(renderer);
			applyButton.Draw(renderer);
			startButton.Draw(renderer);
			wageText.Draw(renderer);
			tierText.Draw(renderer);
		}
	}
	mouse.Draw(renderer);
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
	switch (event.type) {
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (playButton.isSelected) {
					std::cout << "Play button clicked" << std::endl;
					play = true;
				}
				if (searchButton.isSelected) {
					std::cout << "Search button clicked" << std::endl;
					job.Search();
				}
				if (applyButton.isSelected) {
					std::cout << "Apply button clicked" << std::endl;
					job.Apply();
					if (job.hasJob) {
						tierText.UpdateText("Tier: " + job.tier);
					}
				}
				if (startButton.isSelected) {
					std::cout << "Start button clicked" << std::endl;
					if (job.hasJob) {
						job.startJob = true;
					}
				}
			}
	}

}

void Scene1::StartJob(int tier) {
	game->getPlayer()->tier = job.tier;
	tier1.SetVelocity(Vec3(1, -10 + (1/(job.experience + 1) * 1.5f), -1));
	switch (tier) {
	case 1:
		tier1.Draw(renderer, game->getProjectionMatrix(), 0.10f);
		if (tier1.GetPosition().y <= 0) {
			bonus -= 0.1;
			count++;
			tier1.SetPosition(Vec3(rand() % 20, 15, 0));
		}
		else if (tier1.HasIntersection(game->getPlayer()->square)) {
			bonus++;
			count++;
			tier1.SetPosition(Vec3(rand() % 20, 15, 0));
			job.experience++;
		}
		break;
	case 2:

		break;
	case 3:

		break;
	case 4:

		break;
	case 5:

		break;
	}
	if (count == 10) {
		count = 0;
		job.startJob = false;
		job.Wage(bonus);
		bonus = 0;
	}
}