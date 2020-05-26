#include "TitleScreen.h"

TitleScreen::TitleScreen(ApplicationSettings *appSettings)
{
	this->appSettings = appSettings;
	titleContent = new TitleContent(appSettings);

	Tab = ""; isCreate = false;
	Page = "MainMenu";
	mouseX = 0; mouseY = 0;
	setColorText(appSettings->getTheme());
}

TitleScreen::~TitleScreen()
{
	Destroy();
	delete titleContent;
	delete sTitleBackground;
	delete sTitleText;
}

bool TitleScreen::RectCollision(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = Ax;
	rightA = Ax + Aw;
	topA = Ay;
	bottomA = Ay + Ah;

	leftB = Bx;
	rightB = Bx + Bw;
	topB = By;
	bottomB = By + Bh;

	if (bottomA <= topB)
		return false;

	if (topA >= bottomB)
		return false;

	if (rightA <= leftB)
		return false;

	if (leftA >= rightB)
		return false;

	return true;
}

void TitleScreen::setColorText(std::string theme)
{
	if (theme == "Standard")
	{
		colorText.r = 255;
		colorText.g = 255;
		colorText.b = 255;
	}
	else if (theme == "Winter")
	{
		colorText.r = 60;
		colorText.g = 60;
		colorText.b = 60;
	}
}

void TitleScreen::Create(SDL_Renderer *renderer)
{
	if (buttons.size() != 0 || texts.size() != 0)
		Destroy();

	if (Page == "MainMenu")
	{
		texts.push_back(new AnimationText(L"Версия: 0.2a (Декабрь 2016) SDL 2.0.5", 2, 0, colorText.r, colorText.g, colorText.b, 255, 14, 1, renderer));
		texts[0]->setAnimAlpha(0, 8);
		buttons.push_back(new Button(titleContent->getTexture("Button"), L"Начать игру", 300, 400, 200, 60, "Start", renderer));
		buttons.push_back(new Button(titleContent->getTexture("Button"), L"Выбор уровня", 300, 450, 200, 60, "SelectLevel", renderer));
		buttons.push_back(new Button(titleContent->getTexture("Button"), L"Выйти", 300, 500, 200, 60, "Exit", renderer));
		if (appSettings->getTheme() == "Standard")
		    buttons.push_back(new Button(titleContent->getTexture("Button"), L"З", 55, 550, 30, 60, "SwitchTheme", renderer));
		else if (appSettings->getTheme() == "Winter")
			buttons.push_back(new Button(titleContent->getTexture("Button"), L"С", 55, 550, 32, 60, "SwitchTheme", renderer));
		buttons.push_back(new Button(titleContent->getTexture("Button"), L"?", 15, 550, 30, 60, "Info", renderer));
	}
	else if (Page == "SelectLevel")
	{
		if (appSettings->getMaxLevel() >= 1)
		    buttons.push_back(new Button(titleContent->getTexture("Button"), L"Уровень 1", 80, 50, 150, 60, "Level1", renderer));
		if (appSettings->getMaxLevel() >= 2)
		    buttons.push_back(new Button(titleContent->getTexture("Button"), L"Уровень 2", 80, 100, 150, 60, "Level2", renderer));
		if (appSettings->getMaxLevel() >= 3)
		    buttons.push_back(new Button(titleContent->getTexture("Button"), L"Уровень 3", 80, 150, 150, 60, "Level3", renderer));
		if (appSettings->getMaxLevel() >= 4)
			buttons.push_back(new Button(titleContent->getTexture("Button"), L"Уровень 4", 80, 200, 150, 60, "Level4", renderer));
		if (appSettings->getMaxLevel() >= 5)
			buttons.push_back(new Button(titleContent->getTexture("Button"), L"Уровень 5", 80, 250, 150, 60, "Level5", renderer));
		if (appSettings->getMaxLevel() >= 6)
			buttons.push_back(new Button(titleContent->getTexture("Button"), L"Уровень 6", 80, 300, 150, 60, "Level6", renderer));
		if (appSettings->getMaxLevel() >= 7)
			buttons.push_back(new Button(titleContent->getTexture("Button"), L"Уровень 7", 80, 350, 150, 60, "Level7", renderer));

		buttons.push_back(new Button(titleContent->getTexture("Button"), L"Назад", 40, 540, 85, 60, "Back", renderer));
	}
	else if (Page == "Info")
	{
		texts.push_back(new AnimationText(L"Автор: Горбунов Иван", 610, 0, colorText.r, colorText.g, colorText.b, 255, 14, 1, renderer));
		texts[0]->setAnimAlpha(0, 12);
		texts.push_back(new AnimationText(L"Управление:", 90, 50, colorText.r, colorText.g, colorText.b, 255, 20, 1, renderer));
		texts[1]->setAnimAlpha(0, 10);
		texts.push_back(new AnimationText(L"Перемещение: 'Вверх', 'Вниз', 'Влево', 'Вправо';", 40, 90, colorText.r, colorText.g, colorText.b, 255, 16, 1, renderer));
		texts[2]->setAnimAlpha(0, 8);
		texts.push_back(new AnimationText(L"Рестарт: 'R';", 40, 114, colorText.r, colorText.g, colorText.b, 255, 16, 1, renderer));
		texts[3]->setAnimAlpha(0, 6);
		texts.push_back(new AnimationText(L"Пауза: 'P';", 40, 136, colorText.r, colorText.g, colorText.b, 255, 16, 1, renderer));
		texts[4]->setAnimAlpha(0, 4);
		texts.push_back(new AnimationText(L"Debug: 'F1'.", 40, 158, colorText.r, colorText.g, colorText.b, 255, 16, 1, renderer));
		texts[5]->setAnimAlpha(0, 4);
		buttons.push_back(new Button(titleContent->getTexture("Button"), L"Назад", 40, 540, 85, 60, "Back", renderer));
	}
	isCreate = true;
}

void TitleScreen::Destroy()
{
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
		delete (*i);
	for (std::vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); i++)
		delete (*i);
	std::vector<AnimationText*>().swap(texts);
	std::vector<Button*>().swap(buttons);
}

void TitleScreen::Render(SDL_Renderer *renderer)
{
	sTitleBackground->draw(renderer);
	if (Page == "MainMenu")
	    sTitleText->draw(renderer);
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
		(*i)->draw(renderer);
	for (std::vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); i++)
		(*i)->draw(renderer);

	if (!isCreate)
		Create(renderer);
}

void TitleScreen::Update(float deltaTime)
{
	if (Page == "MainMenu")
		sTitleText->update(deltaTime);
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
		(*i)->update(deltaTime);
	for (std::vector<Button*>::iterator i = buttons.begin(); i != buttons.end(); i++){
		if (RectCollision((*i)->getSprite()->getX(), (*i)->getSprite()->getY(), (*i)->getSprite()->getW(), (*i)->getSprite()->getH(), mouseX, mouseY, 1, 1))
		{
			if (!(*i)->getHover()){
				Tab = (*i)->getID();
				(*i)->setHover(true);
				(*i)->hover();
			}
		}
		else if ((*i)->getHover()){
			Tab = "";
			(*i)->setHover(false);
			(*i)->hover();
		}
		(*i)->update(deltaTime);
	}
}

void TitleScreen::Event(SDL_Event e)
{
	if (e.type == SDL_MOUSEMOTION)
	{
		mouseX = e.motion.x;
		mouseY = e.motion.y;
	}
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (Page == "MainMenu")
		{
			if (Tab == "Start"){
				appSettings->setCurrentLevel(1);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "SelectLevel"){
				Page = "SelectLevel";
				isCreate = false;
			}
			else if (Tab == "Exit"){
				appSettings->setExit(true);
			}
			else if (Tab == "Info"){
				Page = "Info";
				isCreate = false;
			}
			else if (Tab == "SwitchTheme"){
				if (appSettings->getTheme() == "Standard")
					appSettings->setThemeWinter();
				else if (appSettings->getTheme() == "Winter")
				    appSettings->setThemeStandard();

				appSettings->LoadTitleScreen();
			}
		}
		if (Page == "SelectLevel")
		{
			if (Tab == "Level1"){
				appSettings->setCurrentLevel(1);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "Level2"){
				appSettings->setCurrentLevel(2);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "Level3"){
				appSettings->setCurrentLevel(3);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "Level4"){
				appSettings->setCurrentLevel(4);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "Level5"){
				appSettings->setCurrentLevel(5);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "Level6"){
				appSettings->setCurrentLevel(6);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "Level7"){
				appSettings->setCurrentLevel(7);
				appSettings->LoadGameScreen();
			}
			else if (Tab == "Back"){
				Page = "MainMenu";
				isCreate = false;
			}
		}
		if (Page == "Info"){
			if (Tab == "Back"){
				Page = "MainMenu";
				isCreate = false;
			}
		}
	}
}

void TitleScreen::LoadContent(SDL_Renderer *renderer)
{
	if (titleContent->Load(renderer))
	{
		sTitleBackground = new Sprite(titleContent->getTexture("TitleBackground"), 0, 0, 800, 600);
		sTitleText = new AnimationSprite(titleContent->getTexture("TitleText"), 165, 120, 450, 240);
		sTitleText->setAnim(3, 1, 150, false);
		Create(renderer);
	}
}

void TitleScreen::UnloadContent()
{
	titleContent->UnLoad();
}