#include "FallingSnow.h"

FallingSnow::FallingSnow(ApplicationSettings *appSettings, GameContent *gameContent)
{
	this->appSettings = appSettings;
	this->gameContent = gameContent;
	currentCount = 0;
	maxCount = 20;
}

FallingSnow::~FallingSnow()
{
	for (std::vector<SnowFlake*>::iterator i = snowFlakes.begin(); i != snowFlakes.end(); i++)
		delete (*i);
	std::vector<SnowFlake*>().swap(snowFlakes);
}

void FallingSnow::Draw(SDL_Renderer *renderer)
{
	for (std::vector<SnowFlake*>::iterator i = snowFlakes.begin(); i != snowFlakes.end(); i++)
		(*i)->Draw(renderer);
}

void FallingSnow::Update(float deltaTime)
{
	if (currentCount < maxCount){
		snowFlakes.push_back(new SnowFlake(gameContent->getTexture("SnowFlake"), rand() % 700 + 10, (rand() % (300 + 10)) * -4, 16, 16));
		currentCount++;
	}

	for (std::vector<SnowFlake*>::iterator i = snowFlakes.begin(); i != snowFlakes.end(); i++)
		(*i)->Update(deltaTime);
}

void FallingSnow::Event(SDL_Event e){}