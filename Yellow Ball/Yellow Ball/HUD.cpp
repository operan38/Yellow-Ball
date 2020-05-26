#include "HUD.h"

HUD::HUD(ApplicationSettings *appSettings, GameContent *gameContent)
{
	this->appSettings = appSettings;
	this->gameContent = gameContent;
	health = 0; money = 0;
	sHealth = new AnimationSprite(gameContent->getTexture("HUDHealth"), 15, 6, 160, 34);
	sHealth->setAnim(2, 8, 350, true);
	sMoney = new Sprite(gameContent->getTexture("HUDMoney"), 105, 5, 18, 18);
	isCreate = false;
}

HUD::~HUD()
{
	Destroy();
	delete sHealth;
	delete sMoney;
}

void HUD::Create(SDL_Renderer *renderer)
{
	texts.push_back(new AnimationText(L" ", 40, 2, 255, 0, 0, 255, 17, 0, "Health", true, renderer));
	texts.push_back(new AnimationText(L" ", 130, 2, 0, 0, 0, 255, 17, 0, "Money", true, renderer));
	texts.push_back(new AnimationText(L" ", 310, 255, 0, 0, 0, 255, 60, 0, "Pause", false, renderer));
	isCreate = true;
}

void HUD::Destroy()
{
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
		delete (*i);
	std::vector<AnimationText*>().swap(texts);
}

void HUD::Pause(bool isPause)
{
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++){
		if ((*i)->getID() == "Pause"){
			if (isPause){
				sHealth->pauseAnim();
				(*i)->setString(L"Пауза");
				(*i)->setAnimMove(310, 230, 1);
				(*i)->setAnimAlpha(0, 10);
				break;
			}
			else {
				sHealth->resumeAnim();
				(*i)->setString(L" ");
				break;
			}
		}
	}
}

void HUD::Draw(SDL_Renderer *renderer)
{
	if (!isCreate)
		Create(renderer);

	sHealth->draw(renderer);
	sMoney->draw(renderer);
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
		(*i)->draw(renderer);
}

void HUD::Update(float deltaTime)
{
	for (std::vector<AnimationText*>::iterator i = texts.begin(); i != texts.end(); i++)
	{
		if ((*i)->getID() == "Health")
			(*i)->setString(std::to_wstring(health));
		if ((*i)->getID() == "Money")
			(*i)->setString(std::to_wstring(money));

		(*i)->update(deltaTime);
	}
	sHealth->update(deltaTime);
}

void HUD::Event(SDL_Event e){}