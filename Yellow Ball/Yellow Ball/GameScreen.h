#pragma once
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "Application.h"
#include "ApplicationMode.h"
#include "ApplicationSettings.h"
#include "GameContent.h"
#include "Sprite.h"
#include "Level.h"
#include "HUD.h"
#include "FallingSnow.h"

class GameScreen : public ApplicationMode
{
    public:
	  GameScreen(ApplicationSettings *appSettings);
	  ~GameScreen();
	  void Render(SDL_Renderer *renderer);
	  void Update(float deltaTime);
	  void Event(SDL_Event e);
	  void LoadContent(SDL_Renderer *renderer);
	  void UnloadContent();
    private:
		ApplicationSettings *appSettings;
		GameContent *gameContent;
		Level *level;
		HUD *hud;
		FallingSnow *fallingSnow;
		bool isPause;
};