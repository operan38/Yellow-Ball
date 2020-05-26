#pragma once
#include "Object.h"
#include "ApplicationSettings.h"
#include "GameContent.h"

class Enemy1 : public Object
{
    public:
	  Enemy1(ApplicationSettings *appSettings, std::string name, GameContent *gameContent, int x, int y, int w, int h, int z_index);
	  ~Enemy1();
	  void Draw(SDL_Renderer *renderer);
	  void Update(float deltaTime);
	  void Event(SDL_Event e);
	  void CheckCollision(Object *object);
    private:
		ApplicationSettings *appSettings;
		GameContent *gameContent;
		Sprite *sprNewYearHats;
		void Move(int dx, int dy);
		int dx, dy, speed;
		int dir;
};