#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Application.h"
#include "ApplicationMode.h"
#include "ApplicationSettings.h"
#include "TitleContent.h"
#include "AnimationText.h"
#include "Button.h"

class TitleScreen : public ApplicationMode
{
    public:
	  TitleScreen(ApplicationSettings *appSettings);
	  ~TitleScreen();
	  void Render(SDL_Renderer *renderer);
	  void Update(float deltaTime);
	  void Event(SDL_Event e);
	  void LoadContent(SDL_Renderer *renderer);
	  void UnloadContent();
    private:
		void Create(SDL_Renderer *renderer);
		void Destroy();
	    bool RectCollision(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh);
		void setColorText(std::string theme);
		SDL_Color colorText;
		int mouseX, mouseY;
		std::string Page, Tab;
		bool isCreate;
		Sprite *sTitleBackground;
		AnimationSprite *sTitleText;
		ApplicationSettings *appSettings;
		TitleContent *titleContent;
		std::vector<AnimationText*> texts;
		std::vector<Button*> buttons;
};