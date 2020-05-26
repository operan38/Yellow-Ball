#include "SnowFlake.h"

SnowFlake::SnowFlake(SDL_Texture *texture, int x, int y, int w, int h)
{
	sprite = new Sprite(texture, x, y, w, h);
	dir = rand() % 2 + 1;
	speed = 1;
	deviation = 0;
	maxDeviation = rand() % 400 + 200;
}

SnowFlake::~SnowFlake()
{
	delete sprite;
}

void SnowFlake::Draw(SDL_Renderer *renderer)
{
	sprite->draw(renderer);
}

void SnowFlake::Update(float deltaTime)
{
	sprite->setY(sprite->getY() + speed);

	if (dir == 1){
		sprite->setX(sprite->getX() + speed);
		deviation++;
		if (deviation > maxDeviation){
			dir = 2;
			deviation = 0;
		}
	}
	else if (dir == 2){
		sprite->setX(sprite->getX() - speed);
		deviation++;
		if (deviation > maxDeviation){
			dir = 1;
			deviation = 0;
		}
	}

	if (sprite->getY() >= 600){
		sprite->setPosition(rand() % 700 + 10, (rand() % (300 + 10)) * -2);
	}

	sprite->update(deltaTime);
}

void SnowFlake::Event(SDL_Event e){}