#pragma once
#include "Sprite.h"

class SnowFlake
{
	public:
		SnowFlake(SDL_Texture *texture, int x, int y, int w, int h);
		~SnowFlake();
		void Draw(SDL_Renderer *renderer);
		void Update(float deltaTime);
		void Event(SDL_Event e);
	private:
		Sprite *sprite;
		int speed;
		int dir;
		int deviation;
		int maxDeviation;
};