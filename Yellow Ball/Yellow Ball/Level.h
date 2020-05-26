#pragma once
#include "ApplicationSettings.h"
#include "GameContent.h"
#include "HUD.h"
#include "Map.h"
#include "Player.h"
#include "Enemy1.h"
#include "Enemy2.h"

class Level
{
    public:
	  Level(ApplicationSettings *appSettings, GameContent *gameContent, HUD *hud);
	  ~Level();
	  void Draw(SDL_Renderer *renderer);
	  void Update(float deltaTime);
	  void Event(SDL_Event e);
    private:
		void CreateObjectsFromMap();
		void InsertSort();
		bool RectCollision(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
		ApplicationSettings *appSettings;
		GameContent *gameContent;
		Sprite *sGameBackground;
		Sprite *sHUDBackground;
		Map *map;
		HUD *hud;
};