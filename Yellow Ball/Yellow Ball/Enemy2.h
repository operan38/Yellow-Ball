#pragma once
#include "Object.h"

class Enemy2 : public Object
{
    public:
	   Enemy2(std::string name, SDL_Texture *texture, int x, int y, int w, int h, int z_index, int dir);
	  ~Enemy2();
	  void Draw(SDL_Renderer *renderer);
	  void Update(float deltaTime);
	  void Event(SDL_Event e);
	  void CheckCollision(Object *object);
    private:
		void Move(int dx, int dy);
		int dx, dy, speed;
		int dir;
};