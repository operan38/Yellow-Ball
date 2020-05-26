#pragma once
#include "ApplicationSettings.h"
#include "GameContent.h"
#include "SnowFlake.h"

class FallingSnow
{
	public:
		FallingSnow(ApplicationSettings *appSettings, GameContent *gameContent);
		~FallingSnow();
		void Draw(SDL_Renderer *renderer);
		void Update(float deltaTime);
		void Event(SDL_Event e);
	private:
		ApplicationSettings *appSettings;
		GameContent *gameContent;
		std::vector<SnowFlake*> snowFlakes;
		int currentCount, maxCount;
};