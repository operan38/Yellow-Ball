#include "NewYearScreen.h"

NewYearScreen::NewYearScreen(ApplicationSettings *appSettings)
{
	this->appSettings = appSettings;
	isCreate = false;
}

void NewYearScreen::Create(SDL_Renderer *renderer)
{
	texts.push_back(new AnimationText(L"С наступающим", 40, 200, 255, 255, 255, 255, 85, 0, "Text1", true, renderer));
	texts[0]->setAnimMove(40, 0, 1);
	texts[0]->setAnimAlpha(0, 1);
	texts.push_back(new AnimationText(L"новым годом! ^_^", 40, 300, 255, 255, 255, 255, 75, 0, "Text2", true, renderer));
	texts[1]->setAnimMove(40, 500, 1);
	texts[1]->setAnimAlpha(0, 1);
	texts.push_back(new AnimationText(L"Счастья, здоровья и побольше подарков в новом году!", 20, 50, 255, 255, 255, 255, 24, 0, "Text3", true, renderer));
	texts[2]->setAnimMove(20, -250, 1);
	texts[2]->setAnimAlpha(0, 1);
	texts.push_back(new AnimationText(L"Спасибо за игру!", 20, 125, 255, 255, 255, 255, 44, 0, "Text4", true, renderer));
	texts[3]->setAnimMove(20, -450, 1);
	texts[3]->setAnimAlpha(0, 1);
	isCreate = true;
}

NewYearScreen::~NewYearScreen()
{
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
		delete (*i);
	std::vector<AnimationText*>().swap(texts);
}

void NewYearScreen::Render(SDL_Renderer *renderer)
{
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
		(*i)->draw(renderer);

	if (!isCreate)
		Create(renderer);
}

void NewYearScreen::Update(float deltaTime)
{
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++){
		if ((*i)->getID() == "Text4"){
			if (!(*i)->getAnimMove())
				appSettings->LoadTitleScreen();
		}

		(*i)->update(deltaTime);
	}
}

void NewYearScreen::Event(SDL_Event e)
{

}

void NewYearScreen::LoadContent(SDL_Renderer *renderer)
{

}

void NewYearScreen::UnloadContent()
{

}