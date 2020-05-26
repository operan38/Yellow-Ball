#pragma once
#include "Application.h"
#include "ApplicationMode.h"
#include "ApplicationSettings.h"
#include "AnimationText.h"
#include "Timer.h"

class NewYearScreen : public ApplicationMode
{
	public:
		NewYearScreen(ApplicationSettings *appSettings);
		~NewYearScreen();
		void Render(SDL_Renderer *renderer);
		void Update(float deltaTime);
		void Event(SDL_Event e);
		void LoadContent(SDL_Renderer *renderer);
		void UnloadContent();
	private:
		ApplicationSettings *appSettings;
		std::vector<AnimationText*> texts;
		bool isCreate;
		void Create(SDL_Renderer *renderer);
};