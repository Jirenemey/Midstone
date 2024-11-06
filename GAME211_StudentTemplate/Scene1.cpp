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
	image = IMG_Load("Textures/Pinky.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	tier1.SetImage(image);
	tier1.SetTexture(texture);
	tier1.SetPosition(Vec3(10, 10, 0));

	tier3.SetImage(image);
	tier3.SetTexture(texture);
	tier3.SetPosition(Vec3(10, 10, 0));

	for (int i = 0; i < tier4Size; i++) {
		tier4[i].SetImage(image);
		tier4[i].SetTexture(texture);
		tier4[i].SetPosition(Vec3(rand() % 30, rand() % 20, 0));
	}

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
	if (job.startJob && job.tier == 4) {
		for (int i = 0; i < tier4Size; i++) {
			tier4[i].Update(deltaTime);
			if(tier4[i].asleep)
				sleepTimer[i] += deltaTime;
		}
	}

	time += deltaTime;
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
						//change tier & wage display
						std::stringstream strm; // for numbers
						strm << "Tier: " << job.tier; // text to change
						tierText.UpdateText(strm.str().c_str()); // display text
						strm.str(std::string()); // clear text
						//repeat for wage

						strm << "Wage: " << job.wage;
						wageText.UpdateText(strm.str().c_str());
						strm.str(std::string());
					}
				}
				if (startButton.isSelected) {
					std::cout << "Start button clicked" << std::endl;
					if (job.hasJob) {
						job.startJob = true;
					}
				}
				if (job.tier == 3) {
					if (tier3.HasIntersection(mouse.rect)) {
						tier3.clicks++;
						std::cout << "Tier 3 Clicks: " << tier3.clicks << std::endl;
					}
				}
				if (job.tier == 4) {
					for (int i = 0; i < tier4Size; i++) {
						if (tier4[i].HasIntersection(mouse.rect) && tier4[i].asleep) {
							tier4[i].clicks++;
							std::cout << "Tier 4 asleep: " << i << "\nClicks: " << tier4[i].clicks << std::endl;
						}
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
			bonus += 0.2;
			count++;
			tier1.SetPosition(Vec3(rand() % 20, 15, 0));
			job.experience++;
		}
		break;
	case 2:

		break;
	case 3:
		tier3.Draw(renderer, game->getProjectionMatrix(), 0.10f);
		if (time > 5) {
			// if robber is in store for more than 5 seconds you lose bonus
			// and you lose 2% of your wallet
			job.wallet -= job.wallet * (0.02f);
			bonus -= 0.1;
			count++;
			tier3.SetPosition(Vec3(rand() % 20, 10, 0));
			tier3.clicks = 0;
			time = 0;
		}
		else if (tier3.clicks == 10) {
			bonus += 0.2;
			count++;
			tier3.SetPosition(Vec3(rand() % 20, 10, 0));
			job.experience++;
			tier3.clicks = 0;
			time = 0;
		}
		break;
	case 4:
		for (int i = 0; i < tier4Size; i++) {
			tier4[i].Draw(renderer, game->getProjectionMatrix(), 0.10f);
			if (sleepTimer[i] > 0) {
				image = IMG_Load("Textures/Blinky.png");
				texture = SDL_CreateTextureFromSurface(renderer, image);
				tier4[i].SetImage(image);
				tier4[i].SetTexture(texture);
			}
			if (sleepTimer[i] > 5 && tier4[i].asleep) {
				// if worker is asleep for more than 5 seconds you lose bonus
				bonus -= 0.1;
				count++;
				sleepTimer[i] = 0;
			}
			else if (tier4[i].clicks == 10) {
				// if worker is asleep and you wake him you get bonus + experience
				bonus += 0.2;
				count++;
				job.experience++;
				tier4[i].clicks = 0;
				sleepTimer[i] = 0;
				tier4[i].asleep = false;
				image = IMG_Load("Pacman.png");
				texture = SDL_CreateTextureFromSurface(renderer, image);
				tier4[i].SetImage(image);
				tier4[i].SetTexture(texture);
			}
		}

		break;
	case 5:

		break;
	}
	if (count == 10 || time == 30) {
		// after each job is complete - reset core mechanics
		// job is reset and you must search and apply for a new one
		count = 0;
		job.startJob = false;
		job.Quit();
		job.applied = true;
		job.Wage(bonus);
		wageText.UpdateText("Wage: ");
		tierText.UpdateText("Tier: ");
		bonus = 1;
		std::cout << "Experience: " << job.experience << std::endl;
	}
}