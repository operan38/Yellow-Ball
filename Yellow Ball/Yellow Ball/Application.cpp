#include "Application.h"

Application::Application() :running(true), MaxFPS(60), AvgFPS(0), frames(0), deltaTime(0){}

Application::~Application()
{
	delete currentScreen;
	delete appSettings;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Application::setScreen(std::string APP_MODE)
{
	if (currentScreen != nullptr)
	{
		currentScreen->UnloadContent();
		delete currentScreen;
	}

	appSettings->setAppModeChange(false);

	if (APP_MODE == "TitleScreen")
		currentScreen = new TitleScreen(appSettings);
	else if (APP_MODE == "GameScreen")
		currentScreen = new GameScreen(appSettings);
	else if (APP_MODE == "NewYearScreen")
		currentScreen = new NewYearScreen(appSettings);

	currentScreen->LoadContent(renderer);
}

bool Application::Init()
{
	setlocale(LC_ALL, "Russian");
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		SDL_Delay(3000);
		return false;
	}
	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "Unable to initialize SDL_image: " << IMG_GetError() << std::endl;
		SDL_Delay(3000);
		return false;
	}
	if (TTF_Init() != 0)
	{
		std::cout << "Unable to initialize SDL_ttf: " << TTF_GetError() << std::endl;
		SDL_Delay(3000);
		return false;
	}
	
	window = SDL_CreateWindow("Yellow Ball", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGTH, SDL_WINDOW_SHOWN);

	if (window == nullptr)
	{
		std::cout << "Unable to initialize window: " << SDL_GetError() << std::endl;
		SDL_Delay(3000);
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		std::cout << "Unable to initialize renderer: " << SDL_GetError() << std::endl;
		SDL_Delay(3000);
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	appSettings = new ApplicationSettings;

	setScreen(appSettings->getAppMode());

	return true;
}

void Application::Loop()
{
	fpsTimer.start(); // Старт таймера FPS
	int frameTicks;
	while (running)
	{
		// Смена режимов окна (меню,игра)
		if (appSettings->getAppModeChange())
			setScreen(appSettings->getAppMode());

		if (MaxFPS != 0)
		    capTimer.start(); // Таймер заморозки фпс

		while (SDL_PollEvent(&e)) // Event
		{
			if (e.type == SDL_QUIT)
				appSettings->setExit(true);
			if (appSettings->getExit())
				running = false;
			if (e.type == SDL_WINDOWEVENT)
			{
				if (e.window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
					appSettings->setAppPause(false);
				else if (e.window.event == SDL_WINDOWEVENT_FOCUS_LOST)
					appSettings->setAppPause(true);
			}
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				if (e.key.keysym.sym == SDLK_F1){
					if (!appSettings->getDebug()){
						appSettings->setDebug(true);
					}
					else{
						appSettings->setDebug(false);
						SDL_SetWindowTitle(window, "Yellow Ball");
					}
				}
			}
			if (!appSettings->getAppPause())
			    currentScreen->Event(e);
		}

		// Счетчик FPS
		if (fpsTimer.getTicks() > 1000)
		{
			AvgFPS = frames;
			frames = 0;
			fpsTimer.start();
		}
		else
		{
			AvgFPS = frames / (fpsTimer.getTicks() / 1000.f);
		}
		if (AvgFPS > 2000000)
			AvgFPS = 0;
		//

		deltaTime = deltaTimer.getTicks() / 1000.f;

		if (!appSettings->getAppPause())
		    currentScreen->Update(deltaTime); // Update

		deltaTimer.start();

		SDL_RenderClear(renderer);

		currentScreen->Render(renderer);

		SDL_RenderPresent(renderer);
		frames++;

		// Заморозка Max FPS
		if (MaxFPS != 0){
			frameTicks = capTimer.getTicks();
			if (frameTicks < 1000 / MaxFPS)
			{
				SDL_Delay(1000 / MaxFPS - frameTicks);
			}
		}
		//

		// Вывод Debug инфо
		if (appSettings->getDebug())
		{
			DEBUG_STR = "(FPS: " + std::to_string((int)AvgFPS) + ") (APP_MODE: " + appSettings->getAppMode() + ") (APP_PAUSE: " + std::to_string(appSettings->getAppPause()) + ")";
			SDL_SetWindowTitle(window, DEBUG_STR.c_str());
		}
		//
	}
}