#include "Enemy1.h"

Enemy1::Enemy1(ApplicationSettings *appSettings, std::string name, GameContent *gameContent, int x, int y, int w, int h, int z_index) :Object(name, gameContent->getTexture("Enemy1"), x, y, w, h, z_index)
{
	this->appSettings = appSettings;
	this->gameContent = gameContent;
	dx = 0; dy = 0;
	speed = 4;
	dir = 4;
	if (appSettings->getTheme() == "Winter") sprNewYearHats = new Sprite(gameContent->getTexture("NewYearHat"), x, y, 40, 40);
}

Enemy1::~Enemy1()
{
	delete sprNewYearHats;
}

void Enemy1::Move(int dx, int dy)
{
	sprite->setPosition(sprite->getX() + dx, sprite->getY() + dy);
}

void Enemy1::Draw(SDL_Renderer *renderer)
{
	Object::Draw(renderer);
	if (appSettings->getTheme() == "Winter") sprNewYearHats->draw(renderer);
}

void Enemy1::Update(float deltaTime)
{
	switch (dir)
	{
	case 1:
		dy = -speed; // Up
		dx = 0;
		Move(0, dy);
		break;
	case 2:
		dy = speed; // Down
		dx = 0;
		Move(0, dy);
		break;
	case 3:
		dx = -speed; // Left
		dy = 0;
		Move(dx, 0);
		break;
	case 4:
		dx = speed; // Right
		dy = 0;
		Move(dx, 0);
		break;
	}
	if (appSettings->getTheme() == "Winter") sprNewYearHats->setPosition(sprite->getX(), sprite->getY() - 30);
}

void Enemy1::CheckCollision(Object *object)
{
	if (object->getName() == "Block" && object->getLife())
	{
		if (dy < 0 && dir == 1)
		{
			dir = 4;
			Move(0, speed);
		}
		else if (dy > 0 && dir == 2)
		{
			dir = 3;
			Move(0, -speed);
		}
		else if (dx < 0 && dir == 3)
		{
			dir = 1;
			Move(speed, 0);
		}
		else if (dx > 0 && dir == 4)
		{
			dir = 2;
			Move(-speed, 0);
		}
	}
}

void Enemy1::Event(SDL_Event e){}