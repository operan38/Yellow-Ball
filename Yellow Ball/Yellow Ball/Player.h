#pragma once
#include "Object.h"
#include "ApplicationSettings.h"
#include "HUD.h"

class Player : public Object
{
    public:
	   Player(ApplicationSettings *appSettings, HUD *hud, std::string name, GameContent *gameContent, int x, int y, int w, int h, int z_index);
	  ~Player();
	  void Draw(SDL_Renderer *renderer);
	  void Update(float deltaTime);
	  void Event(SDL_Event e);
	  void CheckCollision(Object *object);
    private:
		ApplicationSettings *appSettings;
		GameContent *gameContent;
		HUD *hud;
		Sprite *sprNewYearHats;
		void Move(int dx, int dy);
		int dx, dy, speed;
		bool isRightButton, isLeftButton, isUpButton, isDownButton;
		int health;
		int money;
};