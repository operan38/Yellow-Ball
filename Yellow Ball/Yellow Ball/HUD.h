#pragma once
#include <string>
#include "ApplicationSettings.h"
#include "GameContent.h"
#include "AnimationText.h"
#include "AnimationSprite.h"

class HUD
{
   public:
	  HUD(ApplicationSettings *appSettings, GameContent *gameContent);
	 ~HUD();
	 void Draw(SDL_Renderer *renderer);
	 void Update(float deltaTime);
	 void Event(SDL_Event e);
	 void Pause(bool isPause);
	 int getHealth(){ return health; }
	 AnimationSprite *getSpriteHealth(){ return sHealth; }
	 void setHealth(int health){ this->health = health; }
	 void setMoney(int money){ this->money = money; }
   private:
	   int health, money;
	   bool isCreate;
	   void Create(SDL_Renderer *renderer);
	   void Destroy();
	   std::vector<AnimationText*> texts;
	   ApplicationSettings *appSettings;
	   GameContent *gameContent;
	   AnimationSprite *sHealth;
	   Sprite *sMoney;
};