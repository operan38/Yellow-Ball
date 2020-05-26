#pragma once
#define WINDOW_WIDTH 800
#define WINDOW_HEIGTH 600

#include <iostream>
#include <sstream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Timer.h"
#include "ApplicationMode.h"
#include "ApplicationSettings.h"
#include "GameScreen.h"
#include "TitleScreen.h"
#include "NewYearScreen.h"

class Application
{
    public:
	    Application();
	    ~Application();
	    bool Init();
	    void Loop();
    private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Event e;
		Timer fpsTimer, capTimer, deltaTimer;
		bool running;
		int MaxFPS;
		float AvgFPS, frames, deltaTime;
		void setScreen(std::string APP_MODE);
		std::string DEBUG_STR;
		ApplicationMode *currentScreen;
		ApplicationSettings *appSettings;
};