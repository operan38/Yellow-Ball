#include "Sprite.h"

Sprite::Sprite(SDL_Texture *texture, int x, int y, int w, int h)
{
	this->texture = texture;
	srcRect.x = 0; srcRect.y = 0;
	srcRect.w = w; srcRect.h = h;
	dstRect.x = x; dstRect.y = y;
	dstRect.w = w; dstRect.h = h;
}

Sprite::~Sprite(){}

void Sprite::draw(SDL_Renderer *renderer)
{
	SDL_RenderCopy(renderer, texture, &srcRect, &dstRect);
}

void Sprite::update(float deltaTime){}

void Sprite::setPosition(int x, int y)
{
	dstRect.x = x;
	dstRect.y = y;
}

void Sprite::setTextureRect(int x, int y, int w, int h)
{
	srcRect.x = x; srcRect.y = y;
	srcRect.w = w; srcRect.h = h;
	dstRect.w = w; dstRect.h = h;
}

void Sprite::setX(int x){ dstRect.x = x; }

void Sprite::setY(int y){ dstRect.y = y; }

int Sprite::getX(){ return dstRect.x; }

int Sprite::getY(){ return dstRect.y; }

int Sprite::getW(){ return dstRect.w; }

int Sprite::getH(){ return dstRect.h; }