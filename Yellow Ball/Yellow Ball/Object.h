#pragma once
#include <iostream>
#include "AnimationSprite.h"

class Object
{
   public:
	 Object(){}
	 Object(std::string name, SDL_Texture *texture, int x, int y, int w, int h, int z_index)
	 {
		 this->name = name;
		 sprite = new AnimationSprite(texture, x, y, w, h);
		 isLife = true;
		 this->z_index = z_index;
	 }
	 virtual ~Object(){ delete sprite; }
	 virtual void Draw(SDL_Renderer *renderer){ sprite->draw(renderer); }
	 virtual void Update(float deltaTime){ sprite->update(deltaTime); }
	 virtual void Event(SDL_Event e){}
	 virtual void CheckCollision(Object *object){}
	 void setName(std::string name){ this->name = name; }
	 std::string getName(){ return name; }
	 void setLife(bool isLife){ this->isLife = isLife; }
	 bool getLife(){ return isLife; }
	 AnimationSprite *getSprite(){ return sprite; }
	 int getZIndex(){ return z_index; }
	 void setZIndex(int z_index){ this->z_index = z_index; }
   protected:
	   AnimationSprite *sprite;
	   std::string name;
	   bool isLife;
	   int z_index;
};