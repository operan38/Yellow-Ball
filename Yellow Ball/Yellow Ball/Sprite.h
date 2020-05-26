#pragma once
#include <iostream>
#include <SDL.h>

class Sprite
{
    public:
	  Sprite(SDL_Texture *texture, int x, int y, int w, int h);
	  virtual ~Sprite();
	  void draw(SDL_Renderer *renderer);
	  void update(float deltaTime);
	  void setPosition(int x, int y);
	  void setTextureRect(int x, int y, int w, int h);
	  void setX(int x);
	  void setY(int y);
	  int getX();
	  int getY();
	  int getW();
	  int getH();
   protected:
	 SDL_Rect srcRect;
	 SDL_Rect dstRect;
	 SDL_Texture *texture;
};