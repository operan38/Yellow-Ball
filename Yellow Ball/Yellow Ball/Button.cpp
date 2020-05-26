#include "Button.h"

Button::Button(SDL_Texture *texture, std::wstring str, int x, int y, int w, int h, std::string ID, SDL_Renderer *renderer)
{
	this->w = w; this->h = h;
	this->ID = ID;
	text = new AnimationText(str, x + 10, y, 0, 0, 0, 255, 20, 0, renderer);
	sprite = new Sprite(texture, x, y, w, h);
	sprite->setTextureRect(0, 0, w, h/2);
}

Button::~Button()
{
	delete text;
	delete sprite;
}

void Button::draw(SDL_Renderer *renderer)
{
	sprite->draw(renderer);
	text->draw(renderer);
}

void Button::update(float deltaTime)
{
	text->update(deltaTime);
}

void Button::hover()
{
	if (isHover)
	{
		sprite->setTextureRect(0, 30, w, h/2);
		text->setColor(255, 255, 255, 255);
		text->setAnimAlpha(80, 10);
	}
	else if (!isHover)
	{
		sprite->setTextureRect(0, 0, w, h/2);
		text->setColor(0, 0, 0, 255);
	}
}

Sprite *Button::getSprite()
{
	return sprite;
}

std::string Button::getID()
{
	return ID;
}

void Button::setID(std::string ID)
{
	this->ID = ID;
}

void Button::setHover(bool isHover)
{
	this->isHover = isHover;
}

bool Button::getHover()
{
	return isHover;
}