#include "Enemy2.h"

Enemy2::Enemy2(std::string name, SDL_Texture *texture, int x, int y, int w, int h, int z_index, int dir) :Object(name, texture, x, y, w, h, z_index)
{
	dx = 0; dy = 0;
	speed = 4;
	this->dir = dir;
}

Enemy2::~Enemy2(){}

void Enemy2::Move(int dx, int dy)
{
	sprite->setPosition(sprite->getX() + dx, sprite->getY() + dy);
}

void Enemy2::Draw(SDL_Renderer *renderer)
{
	Object::Draw(renderer);
}

void Enemy2::Update(float deltaTime)
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
}

void Enemy2::CheckCollision(Object *object)
{
	if (object->getName() == "Block" && object->getLife())
	{
		if (dy < 0 && dir == 1)
			dir = 2;
		else if (dy > 0 && dir == 2)
			dir = 1;
		else if (dx < 0 && dir == 3)
			dir = 4;
		else if (dx > 0 && dir == 4)
			dir = 3;
	}
}

void Enemy2::Event(SDL_Event e){}