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

	//tier2
	tier2Click = Mix_LoadWAV("Sounds/tier2click.mp3");
	if (!tier2Click)
		std::cout << "Tier2 Click SFX Error: " << Mix_GetError() << std::endl;

	//tier3
	tier3Steal = Mix_LoadWAV("Sounds/tier3steal.mp3");
	if (!tier3Steal)
		std::cout << "Tier3 Steal SFX Error: " << Mix_GetError() << std::endl;

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
	playButton.ChangeSize(500);
	playButton.destinationRect.x = w/2 - playButton.destinationRect.w/2;
	playButton.destinationRect.y = h/2 - playButton.destinationRect.h/2;
	playButton.SetTexture(renderer, "Textures/buttons2.png");
	// main game buttons
	applyButton.sourceRect.y = 100;
	applyButton.ChangeSize(200);
	applyButton.destinationRect.x = w * 0.63;
	applyButton.destinationRect.y = h/12 + 175;
	applyButton.SetTexture(renderer, "Textures/buttons2.png");

	searchButton.sourceRect.y = 400;
	searchButton.ChangeSize(200);
	searchButton.destinationRect.x = w * 0.63;
	searchButton.destinationRect.y = h/12 + 100;
	searchButton.SetTexture(renderer, "Textures/buttons2.png");

	startButton.sourceRect.y = 000;
	startButton.ChangeSize(200);
	startButton.destinationRect.x = w * 0.3;
	startButton.destinationRect.y = h/12 + 275;
	startButton.SetTexture(renderer, "Textures/buttons2.png");

	// upgrade buttons
	upgradeScreenButton.sourceRect.y = 000;
	upgradeScreenButton.ChangeSize(200);
	upgradeScreenButton.destinationRect.x = w * 0.63;
	upgradeScreenButton.destinationRect.y = h/12 + 250;
	upgradeScreenButton.SetTexture(renderer, "Textures/buttons3.png");

	upgradeAccButton.sourceRect.y = 300;
	upgradeAccButton.ChangeSize(200);
	upgradeAccButton.destinationRect.x = w * 0.3;
	upgradeAccButton.destinationRect.y = h/12 + 75;
	upgradeAccButton.SetTexture(renderer, "Textures/buttons3.png");

	upgradeWageButton.sourceRect.y = 100;
	upgradeWageButton.ChangeSize(200);
	upgradeWageButton.destinationRect.x = w * 0.3;
	upgradeWageButton.destinationRect.y = h/12 + 175;
	upgradeWageButton.SetTexture(renderer, "Textures/buttons3.png");

	upgradeExpButton.sourceRect.y = 200;
	upgradeExpButton.ChangeSize(200);
	upgradeExpButton.destinationRect.x = w * 0.3;
	upgradeExpButton.destinationRect.y = h/12 + 275;
	upgradeExpButton.SetTexture(renderer, "Textures/buttons3.png");

	backButton.sourceRect.y = 200;
	backButton.ChangeSize(200);
	backButton.destinationRect.x = w * 0.06;
	backButton.destinationRect.y = h/12 + 50;
	backButton.SetTexture(renderer, "Textures/buttons2.png");

	// TEXTS
	// menu
	titleText.x = w/3;
	titleText.y = h/12;
	// left computer screen
	jobInfoText.x = w/5;
	jobInfoText.y = h/12 + 50;
	wageText.x = w/10;
	wageText.y = h/12 + 125;
	tierText.x = w/10;
	tierText.y = h/12 + 175;
	walletText.x = w/10;
	walletText.y = h/12 + 225;
	experienceText.x = w/10;
	experienceText.y = h/12 + 275;
	
	//right computer screen
	searchInfoText.x = w/2;
	searchInfoText.y = h / 12 + 50;
	searchTierText.x = w * 0.475;
	searchTierText.y = h / 12 + 125;
	searchWageText.x = w * 0.475;
	searchWageText.y = h / 12 + 175;

	//upgrade screen texts - right computer
	upgradePrice.x = w * 0.475;
	upgradePrice.y = h / 12 + 75;
	upgradeLevel.x = w * 0.475;
	upgradeLevel.y = h / 12 + 175;
	upgradeDesc.x = w * 0.475;
	upgradeDesc.y = h / 12 + 275;



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
	// initial spawn & vel
	tier1.SetPosition(Vec3(10, 10, 0));
	tier1.SetVelocity(Vec3(0, -10 + (1 / (job.experience + 1) * 1.5f), -1));

	//tier2 background
	tier2Background = IMG_Load("Textures/Tier2Background.png");
	BackgroundTexture2 = SDL_CreateTextureFromSurface(renderer, tier2Background);
	//tier2 items
	tier2Assets[0] = "Textures/Box1.png";
	tier2Assets[1] = "Textures/Box2.png";
	tier2Assets[2] = "Textures/Box3.png";
	tier2Assets[3] = "Textures/Box4.png";
	
	for (int i = 0; i < tier2Size; i++) {
		image = IMG_Load(tier2Assets[rand() % 4]);
		texture = SDL_CreateTextureFromSurface(renderer, image);
		tier2[i].SetImage(image);
		tier2[i].SetTexture(texture);
		// initial spawn & vel
		tier2[i].SetPosition(Vec3(-1, rand() % 15, 0));
		tier2[i].SetVelocity(Vec3(rand() % 10 + (10 / (job.experience + 1)), 0, -1));
	}

	//tier2 button
	tier2CounterBtn.sourceRect.y = 000;
	tier2CounterBtn.destinationRect.x = w - (w * 1 / 1.5);
	tier2CounterBtn.destinationRect.y = h - h / 6;
	tier2CounterBtn.SetTexture(renderer, "Textures/RedButton.png");

	//tier3 background
	tier3Background = IMG_Load("Textures/Tier3Background.png");
	BackgroundTexture3 = SDL_CreateTextureFromSurface(renderer, tier3Background);
	//tier3 item
	image = IMG_Load("Textures/Tier3ShadowLeft.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	tier3.SetImage(image);
	tier3.SetTexture(texture);
	tier3.SetPosition(Vec3(10, 5, 0));


	//tier4 background
	tier4Background = IMG_Load("Textures/Tier4Background.png");
	BackgroundTexture4 = SDL_CreateTextureFromSurface(renderer, tier4Background);
	//tier4 item
	image = IMG_Load("Textures/NoImage.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	for (int i = 0; i < tier4Size; i++) {
		tier4[i].SetImage(image);
		tier4[i].SetTexture(texture);
	}
	tier4[0].SetPosition(Vec3(11, 9.85, 0));
	tier4[1].SetPosition(Vec3(5.2, 7.9, 0));
	tier4[2].SetPosition(Vec3(16.8, 11.9, 0));
	tier4[3].SetPosition(Vec3(19.2, 7.1, 0));
	tier4[4].SetPosition(Vec3(13.4, 5.1, 0));
	tier4[5].SetPosition(Vec3(2.8, 12.6, 0));

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
	if(!play)
		playButton.Update(mouse);
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

	if (job.startJob && job.tier == 2) {
		tier2CounterBtn.Update(mouse);
		for (int i = 0; i < tier2Size; i++) {
				tier2[i].Update(deltaTime);
		}
	}

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
		upgradePrice.Draw(renderer);
		upgradeLevel.Draw(renderer);
		if (upgradeAccButton.isSelected || upgradeExpButton.isSelected || upgradeWageButton.isSelected)
			upgradeDesc.Draw(renderer);
	}
	else {
		if (job.startJob) {
			StartJob(job.tier);
			if(job.tier == 1)
				game->getPlayer()->Render(0.20f);
			if (job.tier == 2)
				tier2CounterBtn.Draw(renderer);

		}
		else {
			SDL_RenderCopy(renderer, gameBackgroundTexture, NULL, NULL);
			searchButton.Draw(renderer);
			applyButton.Draw(renderer);
			startButton.Draw(renderer);
			upgradeScreenButton.Draw(renderer);
			jobInfoText.Draw(renderer);
			wageText.Draw(renderer);
			tierText.Draw(renderer);
			walletText.Draw(renderer);
			experienceText.Draw(renderer);
			searchInfoText.Draw(renderer);
			searchTierText.Draw(renderer);
			searchWageText.Draw(renderer);
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
						searchTierText.UpdateText(SetText("Tier: ", job.tier));
						searchWageText.UpdateText(SetText("Wage: ", job.wage));
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
					walletText.x = backButton.destinationRect.x + 60;
					walletText.y = backButton.destinationRect.y + 150;
					if (upgradeAccButton.isSelected)
						job.UpgradeJobAcc();
					if (upgradeExpButton.isSelected)
						job.UpgradeExperience();
					if (upgradeWageButton.isSelected)
						job.UpgradeWage();
					walletText.UpdateText(SetText("Wallet: $", job.wallet));
					std::cout << "Wallet: " << job.wallet << std::endl;
					Mix_PlayChannel(-1, clickSound, 0);

				}
				if (upgradeScreen) {
					if (backButton.isSelected) {
						std::cout << "Back button clicked" << std::endl;
						upgradeScreen = false;
						backButton.isSelected = false;
						walletText.x = tierText.x;
						walletText.y = tierText.y + 50;
						walletText.UpdateText(SetText("Wallet: $", job.wallet));
						Mix_PlayChannel(-1, clickSound, 0);
					}

					if (upgradeAccButton.isSelected) 
						job.UpgradeJobAcc();
					if (upgradeExpButton.isSelected)
						job.UpgradeExperience();
					if (upgradeWageButton.isSelected)
						job.UpgradeWage();
					walletText.UpdateText(SetText("Wallet: $", job.wallet));
					Mix_PlayChannel(-1, clickSound, 0);

				}
				if (job.startJob) {
					if (job.tier == 2) {
						if (tier2CounterBtn.isSelected) {
							tier2CounterPlayer++;
							std::cout << "The Counter Has Increased: " << tier2CounterPlayer << std::endl;
							Mix_PlayChannel(-1, tier2Click, 0);
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
			break;
		case SDL_MOUSEMOTION:
			if (upgradeAccButton.isSelected) {
				upgradeDesc.UpdateText("Increases job acceptance chance.");
				upgradePrice.UpdateText(SetText("Price: ", job.jobAccChancePrice));
				upgradeLevel.UpdateText(SetText("Level: ", job.jobAccChanceLevel));
			}
			if (upgradeExpButton.isSelected) {
				upgradeDesc.UpdateText("Increases job experience.");
				upgradePrice.UpdateText(SetText("Price: ", job.experiencePrice));
				upgradeLevel.UpdateText(SetText("Level: ", job.experienceLevel));
			}
			if (upgradeWageButton.isSelected) {
				upgradeDesc.UpdateText("Increases job wage multi.");
				upgradePrice.UpdateText(SetText("Price: ", job.wageUpgradePrice));
				upgradeLevel.UpdateText(SetText("Level: ", job.wageUpgradeLevel));
			}
			break;
	}

}

void Scene1::StartJob(int tier) {
	game->getPlayer()->tier = job.tier;
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
			tier1.SetVelocity(Vec3(0, -10 + (1 / (job.experience + 1) * 1.5f), -1));
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
			tier1.SetVelocity(Vec3(0, -10 + (1 / (job.experience + 1) * 1.5f), -1));
			Mix_PlayChannel(-1, point, 0);
		}
		break;
	case 2:
		SDL_RenderCopy(renderer, BackgroundTexture2, NULL, NULL);
		for (int i = 0; i < tier2Size; i++){
			tier2[i].Draw(renderer, game->getProjectionMatrix(), 4.0f);
			if (tier2[i].GetPosition().x >= 25 && time <= 25) {
				tier2Counter++;
				std::cout << "The Object Counter Has Increased: " << tier2Counter << std::endl;
				tier2[i].SetPosition(Vec3(-1, rand() % 10 + 5, 0));
				image = IMG_Load(tier2Assets[rand() % 4]);
				texture = SDL_CreateTextureFromSurface(renderer, image);
				tier2[i].SetImage(image);
				tier2[i].SetTexture(texture);
				tier2[i].SetVelocity(Vec3(rand() % 10 + (10 / (job.experience + 1) * 1.5f), 0, -1));
				Mix_PlayChannel(-1, point, 0);
			}
		}
		if(time >= 30){
			if (tier2Counter == tier2CounterPlayer) {
				bonus = 3;
				job.experience += 10;
			}
			else if (tier2Counter > tier2CounterPlayer && tier2Counter < tier2CounterPlayer + 5) {
				bonus = 1.5;
				job.experience += 5;
			}
			else if (tier2Counter < tier2CounterPlayer && tier2Counter > tier2CounterPlayer - 5) {
				bonus = 1.5;
				job.experience += 5;
			}
			else
				bonus = 0.5;
		}
		break;
	case 3:
		tier3.Draw(renderer, game->getProjectionMatrix(), 5.0f);
		tier3Clicks = 10 - (job.experience / 25);
		tier3Time = 2 + (job.experience / 25);
		if (tier3Clicks < 1)
			tier3Clicks = 1;
		SDL_RenderCopy(renderer, BackgroundTexture3, NULL, NULL);
		if (time > tier3Time) {
			// if robber is in store for more than 5 seconds you lose bonus
			// and you lose 2% of your wallet (got robbed)
			job.wallet -= job.wallet * (0.02f);
			bonus -= 0.1;
			count++;
			tier3.SetPosition(Vec3(rand() % 20, 5, 0));
			tier3.clicks = 0;
			time = 0;
			Mix_PlayChannel(-1, tier3Steal, 0);
		}
		else if (tier3.clicks >= tier3Clicks) {
			bonus += 0.2;
			count++;
			tier3.SetPosition(Vec3(rand() % 15 + 5, 5, 0));
			job.experience++;
			tier3.clicks = 0;
			time = 0;
			Mix_PlayChannel(-1, point, 0);
		}
		break;
	case 4:
		SDL_RenderCopy(renderer, BackgroundTexture4, NULL, NULL);
		for (int i = 0; i < tier4Size; i++) {
			tier4[i].Draw(renderer, game->getProjectionMatrix(), 6.0f);
			tier4Clicks = 7 - (job.experience / 50);
			if (tier4Clicks < 1)
				tier4Clicks = 1;
			if (sleepTimer[i] > 0 && !tier4[i].sleepImage) {
				tier4[i].sleepImage = true;
				image = IMG_Load("Textures/Tier4Asleep.png");
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
			else if (tier4[i].clicks >= tier4Clicks) {
				// if worker is asleep and you wake him you get bonus + experience
				bonus += 0.2;
				count++;
				job.experience++;
				tier4[i].clicks = 0;
				sleepTimer[i] = 0;
				image = IMG_Load("Textures/NoImage.png");
				texture = SDL_CreateTextureFromSurface(renderer, image);
				tier4[i].SetImage(image);
				tier4[i].SetTexture(texture);
				tier4[i].sleepImage = false;
				tier4[i].asleep = false;
				Mix_PlayChannel(-1, point, 0);
			}
		}
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
			image = IMG_Load("Textures/NoImage.png");
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
		strm << text << num / 1000000 << std::setprecision(2) << " M";
	else
		strm << text << num << std::setprecision(2);

	return strm.str().c_str();
}