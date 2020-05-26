#include "GameScreen.h"

GameScreen::GameScreen(ApplicationSettings *appSettings)
{
	this->appSettings = appSettings;
	gameContent = new GameContent(appSettings);

	isPause = false;
}

GameScreen::~GameScreen()
{
	if (fallingSnow != nullptr)
		delete fallingSnow;

	delete level;
	delete hud;
	delete gameContent;
}

void GameScreen::Render(SDL_Renderer *renderer)
{
	level->Draw(renderer);

	if (appSettings->getTheme() == "Winter")
		fallingSnow->Draw(renderer);

	hud->Draw(renderer);

	// Переход на следующий уровень
	if (appSettings->getNextLevel())
	{
		appSettings->setCurrentLevel(appSettings->getCurrentLevel() + 1);
		if (appSettings->getMaxLevel() < appSettings->getCurrentLevel())
			appSettings->setMaxLevel(appSettings->getCurrentLevel());

		appSettings->setNextLevel(false);
		delete level;
		//gameContent->CheckContent(renderer);
		level = new Level(appSettings, gameContent, hud);
	}
}

void GameScreen::Update(float deltaTime)
{
	if (!isPause){
		level->Update(deltaTime);

		if (appSettings->getTheme() == "Winter")
			fallingSnow->Update(deltaTime);
	}

	hud->Update(deltaTime);
}

void GameScreen::Event(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (e.key.keysym.sym == SDLK_r)
		{
			if (hud->getHealth() <= 0 && !isPause){
				delete level;
				level = new Level(appSettings, gameContent, hud);
			}
		}
		if (e.key.keysym.sym == SDLK_p)
		{
			if (!isPause){
				isPause = true;
				hud->Pause(isPause);
			}
			else{
				isPause = false;
				hud->Pause(isPause);
			}
		}
		if (e.key.keysym.sym == SDLK_ESCAPE)
			appSettings->LoadTitleScreen();
	}
	if (!isPause)
	    level->Event(e);

	hud->Event(e);
}

void GameScreen::LoadContent(SDL_Renderer *renderer)
{
	if (gameContent->Load(renderer))
	{
		hud = new HUD(appSettings, gameContent);
		level = new Level(appSettings, gameContent, hud);

		if (appSettings->getTheme() == "Winter")
			fallingSnow = new FallingSnow(appSettings, gameContent);

	}
}

void GameScreen::UnloadContent()
{
	gameContent->UnLoad();
}