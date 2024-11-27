#include "Scene1.h"
#include <VMath.h>
#include <iomanip>

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

	// Turn on SDL mixer - music stuff
	Mix_Init(MIX_INIT_MP3);

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	menuMusic = Mix_LoadMUS("Sounds/menu.mp3");
	if (!menuMusic) 
		std::cout << "Music Error: " << Mix_GetError() << std::endl;
	
	clickSound = Mix_LoadWAV("Sounds/button.mp3");
	if (!clickSound) 
		std::cout << "Button SFX Error: " << Mix_GetError() << std::endl;
	
	//universal win
	point = Mix_LoadWAV("Sounds/point.mp3");
	if (!point)
		std::cout << "Win SFX Error: " << Mix_GetError() << std::endl;
	//tier1
	tier1Fall = Mix_LoadWAV("Sounds/tier1fall.mp3");
	if (!tier1Fall)
		std::cout << "Tier1 Fall SFX Error: " << Mix_GetError() << std::endl;

	//tier4
	tier4Sleep = Mix_LoadWAV("Sounds/tier4asleep.mp3");
	if(!tier4Sleep)
		std::cout << "Tier4 Asleep SFX Error: " << Mix_GetError() << std::endl;

	Mix_PlayMusic(menuMusic, -1);

	// mouse cursor
	image = IMG_Load("mouse.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	mouse.SetTexture(texture);

	// setting all buttons with images and location on screen
	// start menu button
	playButton.sourceRect.y = 600;
	playButton.destinationRect.x = w/2 - playButton.sourceRect.w/2;
	playButton.destinationRect.y = h/2 - playButton.sourceRect.h/2;
	playButton.SetTexture(renderer, "Textures/buttons2.png");
	// main game buttons
	applyButton.sourceRect.y = 100;
	applyButton.destinationRect.x = w - w/3;
	applyButton.destinationRect.y = h - h/4;
	applyButton.SetTexture(renderer, "Textures/buttons2.png");

	searchButton.sourceRect.y = 400;
	searchButton.destinationRect.x = w - w/3;
	searchButton.destinationRect.y = h - (h * 3/7);
	searchButton.SetTexture(renderer, "Textures/buttons2.png");

	startButton.sourceRect.y = 000;
	startButton.destinationRect.x = w - (w * 4 / 5);
	startButton.destinationRect.y = h - h / 4;
	startButton.SetTexture(renderer, "Textures/buttons2.png");

	// upgrade buttons
	upgradeScreenButton.sourceRect.y = 000;
	upgradeScreenButton.destinationRect.x = w - w / 3;
	upgradeScreenButton.destinationRect.y = h - h/ 2;
	upgradeScreenButton.SetTexture(renderer, "Textures/buttons3.png");

	upgradeAccButton.sourceRect.y = 300;
	upgradeAccButton.destinationRect.x = w - (w * 0.95);
	upgradeAccButton.destinationRect.y = h - h / 2;
	upgradeAccButton.SetTexture(renderer, "Textures/buttons3.png");

	upgradeWageButton.sourceRect.y = 100;
	upgradeWageButton.destinationRect.x = w - (w * 0.95) + 300;
	upgradeWageButton.destinationRect.y = h - h / 2;
	upgradeWageButton.SetTexture(renderer, "Textures/buttons3.png");

	upgradeExpButton.sourceRect.y = 200;
	upgradeExpButton.destinationRect.x = w - (w * 0.95) + 600;
	upgradeExpButton.destinationRect.y = h - h / 2;
	upgradeExpButton.SetTexture(renderer, "Textures/buttons3.png");

	backButton.sourceRect.y = 200;
	backButton.destinationRect.x = 0;
	backButton.destinationRect.y = h - (h * 9/10) ;
	backButton.SetTexture(renderer, "Textures/buttons2.png");

	//texts
	titleText.x = w/4;
	titleText.y = h/12;

	tierText.y = h/12;
	walletText.y = h/12 + 50;
	experienceText.y = h/12 + 100;
	border = new SDL_Rect();
	border->w = w - w/15;
	border->h = h - h/15;
	border->x = w/2 - border->w/2;
	border->y = h/2 - border->h/2;

	//menu background
	menuBackground = IMG_Load("Textures/Menu_background.jpg");
	menuBackgroundTexture = SDL_CreateTextureFromSurface(renderer, menuBackground);

	//main game background
	gameBackground = IMG_Load("Textures/Midstone_background.png");
	gameBackgroundTexture = SDL_CreateTextureFromSurface(renderer, gameBackground);

	// tier1 background
	tier1Background = IMG_Load("Textures/ShoppingAisle.png");
	tier1BackgroundTexture = SDL_CreateTextureFromSurface(renderer, tier1Background);
	// tier1 player
	image = IMG_Load("Textures/ShoppingCart.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);
	// tier1 assets - 4 of them
	tier1Assets[0] = "Textures/PurpleBox.png";
	tier1Assets[1] = "Textures/Bottle.png";
	tier1Assets[2] = "Textures/CanTomatoes.png";
	tier1Assets[3] = "Textures/BrownBox.png";
	image = IMG_Load(tier1Assets[rand() % 4]);
	texture = SDL_CreateTextureFromSurface(renderer, image);
	tier1.SetImage(image);
	tier1.SetTexture(texture);
	// initial spawn
	tier1.SetPosition(Vec3(10, 10, 0));

	//tier2 background
	tier2Background = IMG_Load("Textures/Tier2Background.png");
	BackgroundTexture2 = SDL_CreateTextureFromSurface(renderer, tier2Background);
	//tier2 items
	tier2Assets[0] = "Textures/Box1.png";
	tier2Assets[1] = "Textures/Box2.png";
	tier2Assets[2] = "Textures/Box3.png";
	tier2Assets[3] = "Textures/Box4.png";
	image = IMG_Load(tier2Assets[rand() % 4]);
	texture = SDL_CreateTextureFromSurface(renderer, image);
	tier2.SetImage(image);
	tier2.SetTexture(texture);
	// initial spawn
	tier2.SetPosition(Vec3(1, 10, 0));
	//tier2 button
	tier2CounterBtn.sourceRect.y = 000;
	tier2CounterBtn.destinationRect.x = w - (w * 1 / 1.5);
	tier2CounterBtn.destinationRect.y = h - h / 6;
	tier2CounterBtn.SetTexture(renderer, "Textures/RedButton.png");

	tier3.SetImage(image);
	tier3.SetTexture(texture);
	tier3.SetPosition(Vec3(10, 10, 0));

	for (int i = 0; i < tier4Size; i++) {
		tier4[i].SetImage(image);
		tier4[i].SetTexture(texture);
		tier4[i].SetPosition(Vec3(rand() % 20 + 5, rand() % 20 + 5, 0));
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
	tier2.Update(deltaTime);
	tier2CounterBtn.Update(mouse);
	if (play && !upgradeScreen) {
		applyButton.Update(mouse);
		searchButton.Update(mouse);
		startButton.Update(mouse);
		upgradeScreenButton.Update(mouse);
	}
	if (upgradeScreen) {
		upgradeAccButton.Update(mouse);
		upgradeExpButton.Update(mouse);
		upgradeWageButton.Update(mouse);
		backButton.Update(mouse);
	}
	if(job.tier == 1)
		tier1.Update(deltaTime);
	if (job.startJob && job.tier == 4) {
		for (int i = 0; i < tier4Size; i++) {
			if(tier4[i].asleep)
				sleepTimer[i] += deltaTime;
			else
				tier4[i].Update(deltaTime);
		}
	}

	time += deltaTime;
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
	//SDL_RenderCopy(renderer, BackgroundTexture, NULL, NULL);

	// render the player
	if (!play) {
		SDL_RenderCopy(renderer, menuBackgroundTexture, NULL, NULL);
		playButton.Draw(renderer);
		titleText.Draw(renderer);
	}
	else if (upgradeScreen) {
		SDL_RenderCopy(renderer, gameBackgroundTexture, NULL, NULL);
		upgradeAccButton.Draw(renderer);
		upgradeExpButton.Draw(renderer);
		upgradeWageButton.Draw(renderer);
		backButton.Draw(renderer);
		walletText.Draw(renderer);
	}
	else {
		if (job.startJob) {
			StartJob(job.tier);
<<<<<<< HEAD
			if(job.tier == 1)
				game->getPlayer()->Render(0.20f);
			if (job.tier == 2)
				tier2CounterBtn.Draw(renderer);
=======
>>>>>>> kumanan-branch
		}
		else {
			SDL_RenderCopy(renderer, gameBackgroundTexture, NULL, NULL);
			searchButton.Draw(renderer);
			applyButton.Draw(renderer);
			startButton.Draw(renderer);
			upgradeScreenButton.Draw(renderer);
			wageText.Draw(renderer);
			tierText.Draw(renderer);
			walletText.Draw(renderer);
			experienceText.Draw(renderer);
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
				if (playButton.isSelected && play == false) {
					std::cout << "Play button clicked" << std::endl;
					play = true;
					Mix_PlayChannel(-1, clickSound, 0);
				}
				if (play && !upgradeScreen && !job.startJob) {
					if (searchButton.isSelected) {
						std::cout << "Search button clicked" << std::endl;
						// remember to display tier and wage values before being accepted or declined as the console will not be present during gameplay
						job.Search();
						Mix_PlayChannel(-1, clickSound, 0);
					}
					if (applyButton.isSelected) {
						std::cout << "Apply button clicked" << std::endl;
						job.Apply();
						if (job.hasJob) {
							tierText.UpdateText(SetText("Tier: ", job.tier)); // display text
							wageText.UpdateText(SetText("Wage: $", job.wage));
							Mix_PlayChannel(-1, clickSound, 0);
						}
					}
					if (startButton.isSelected) {
						std::cout << "Start button clicked" << std::endl;
						if (job.hasJob) {
							job.startJob = true;
							time = 0;
							Mix_PlayChannel(-1, clickSound, 0);
						}
					}
				}
				if (upgradeScreenButton.isSelected && !upgradeScreen && !job.startJob) {
					std::cout << "Upgrade button clicked" << std::endl;
					upgradeScreen = true;
					walletText.x = backButton.destinationRect.x + 300;
					walletText.y = backButton.destinationRect.y;
<<<<<<< HEAD
					if (upgradeAccButton.isSelected)
						job.UpgradeJobAcc();
					if (upgradeExpButton.isSelected)
						job.UpgradeExperience();
					if (upgradeWageButton.isSelected)
						job.UpgradeWage();
					walletText.UpdateText(SetText("Wallet: $", job.wallet));
					std::cout << "Wallet: " << job.wallet << std::endl;
=======
					Mix_PlayChannel(-1, clickSound, 0);
>>>>>>> kumanan-branch
				}
				if (upgradeScreen) {
					if (backButton.isSelected) {
						std::cout << "Back button clicked" << std::endl;
						upgradeScreen = false;
						backButton.isSelected = false;
						walletText.x = 0;
						walletText.y = tierText.y + 50;
						walletText.UpdateText(SetText("Wallet: $", job.wallet));
						Mix_PlayChannel(-1, clickSound, 0);
					}
<<<<<<< HEAD
=======
					if (upgradeAccButton.isSelected) 
						job.UpgradeJobAcc();
					if (upgradeExpButton.isSelected)
						job.UpgradeExperience();
					if (upgradeWageButton.isSelected)
						job.UpgradeWage();
					walletText.UpdateText(SetText("Wallet: $", job.wallet));
					Mix_PlayChannel(-1, clickSound, 0);
>>>>>>> kumanan-branch
				}
				if (job.startJob) {
					if (job.tier == 2) {
						if (tier2CounterBtn.isSelected) {
							tier2CounterPlayer++;
							std::cout << "The Counter Has Increased: " << tier2CounterPlayer << std::endl;
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

}

void Scene1::StartJob(int tier) {
	game->getPlayer()->tier = job.tier;
	tier1.SetVelocity(Vec3(0, -10 + (1/(job.experience + 1) * 1.5f), -1));
	tier2.SetVelocity(Vec3(10 + (1 / (job.experience + 1) * 1.5f), 0, -1));
	switch (tier) {
	case 1:
		SDL_RenderCopy(renderer, tier1BackgroundTexture, NULL, NULL);
		tier1.Draw(renderer, game->getProjectionMatrix(), 0.15f);
		game->getPlayer()->Render(0.20f);
		if (tier1.GetPosition().y <= 0) {
			bonus -= 0.1;
			count++;
			tier1.SetPosition(Vec3(rand() % 20, 15, 0));
			image = IMG_Load(tier1Assets[rand() % 4]);
			texture = SDL_CreateTextureFromSurface(renderer, image);
			tier1.SetImage(image);
			tier1.SetTexture(texture);
			Mix_PlayChannel(-1, tier1Fall, 0);
		}
		else if (tier1.HasIntersection(game->getPlayer()->square)) {
			bonus += 0.2;
			count++;
			tier1.SetPosition(Vec3(rand() % 20, 15, 0));
			job.experience++;
			image = IMG_Load(tier1Assets[rand() % 4]);
			texture = SDL_CreateTextureFromSurface(renderer, image);
			tier1.SetImage(image);
			tier1.SetTexture(texture);
			Mix_PlayChannel(-1, point, 0);
		}
		break;
	case 2:
		SDL_RenderCopy(renderer, BackgroundTexture2, NULL, NULL);
		tier2.Draw(renderer, game->getProjectionMatrix(), 4.0f);
		if (tier2.GetPosition().x >= 25) {
			count++;
			std::cout << "The Object Counter Has Increased: " << tier2Counter << std::endl;
			tier2Counter++;
			tier2.SetPosition(Vec3(-1, rand() % 15, 0));
			image = IMG_Load(tier2Assets[rand() % 4]);
			texture = SDL_CreateTextureFromSurface(renderer, image);
			tier2.SetImage(image);
			tier2.SetTexture(texture);
		}
		if (tier2Counter == tier2CounterPlayer) {

		}
		break;
	case 3:
		tier3.Draw(renderer, game->getProjectionMatrix(), 0.10f);
		if (time > 5) {
			// if robber is in store for more than 5 seconds you lose bonus
			// and you lose 2% of your wallet (got robbed)
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
			Mix_PlayChannel(-1, point, 0);
		}
		break;
	case 4:
		for (int i = 0; i < tier4Size; i++) {
			tier4[i].Draw(renderer, game->getProjectionMatrix(), 0.10f);
			if (sleepTimer[i] > 0 && !tier4[i].sleepImage) {
				tier4[i].sleepImage = true;
				image = IMG_Load("Textures/Blinky.png");
				texture = SDL_CreateTextureFromSurface(renderer, image);
				tier4[i].SetImage(image);
				tier4[i].SetTexture(texture);
				Mix_PlayChannel(-1, tier4Sleep, 0);
			}
			if (sleepTimer[i] > 5 && tier4[i].asleep) {
				// if worker is asleep for more than 5 seconds you lose bonus
				bonus -= 0.1;
				count++;
				sleepTimer[i] = 0;
				Mix_PlayChannel(-1, tier4Sleep, 0);
			}
			else if (tier4[i].clicks == 5) {
				// if worker is asleep and you wake him you get bonus + experience
				bonus += 0.2;
				count++;
				job.experience++;
				tier4[i].clicks = 0;
				sleepTimer[i] = 0;
				image = IMG_Load("Pacman.png");
				texture = SDL_CreateTextureFromSurface(renderer, image);
				tier4[i].SetImage(image);
				tier4[i].SetTexture(texture);
				tier4[i].sleepImage = false;
				tier4[i].asleep = false;
				Mix_PlayChannel(-1, point, 0);
			}
		}

		break;
	case 5:

		break;
	}
	if (count == 10 || time >= 30) {
		// after each job is complete - reset core mechanics
		// job is reset and you must search and apply for a new one
		count = 0;
		job.startJob = false;
		job.Quit();
		job.applied = true;
		job.Wage(bonus);
		bonus = 1;
		for (int i = 0; i < tier4Size; i++) {
			tier4[i].asleep = false;
			tier4[i].sleepImage = false;
			image = IMG_Load("Pacman.png");
			texture = SDL_CreateTextureFromSurface(renderer, image);
			tier4[i].SetImage(image);
			tier4[i].SetTexture(texture);
		}

		//reset the tier2 counters
		tier2Counter = 0;
		tier2CounterPlayer = 0;

		// update gui
		wageText.UpdateText("Wage: $0");
		tierText.UpdateText("Tier: N/A");
		walletText.UpdateText(SetText("Wallet: $", job.wallet));
		experienceText.UpdateText(SetText("Exp: ", job.experience));
		std::cout << "Experience: " << job.experience << std::endl;
	}
}

std::string Scene1::SetText(const char* text, float num)
{
	// in order to display numbers
	std::stringstream strm;
	if (num >= 1000000)
		strm << text << num / 1000000 << std::setprecision(2) << " Million";
	else
		strm << text << num << std::setprecision(2);

	return strm.str().c_str();
}