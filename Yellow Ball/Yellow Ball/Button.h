#pragma once
#include "AnimationText.h"
#include "AnimationSprite.h"

class Button
{
   public:
	  Button(SDL_Texture *texture, std::wstring str, int x, int y, int w, int h, std::string ID, SDL_Renderer *renderer);
	 ~Button();
	 void draw(SDL_Renderer *renderer);
	 void update(float deltaTime);
	 std::string getID();
	 void setID(std::string ID);
	 void setHover(bool isHover);
	 bool getHover();
	 void hover();
	 Sprite *getSprite();
   private:
	   int w, h;
	   AnimationText *text;
	   Sprite *sprite;
	   std::string ID;
	   bool isHover;
};