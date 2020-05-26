#pragma once
#include "SDL.h"

class ApplicationMode
{
    public:
	  ApplicationMode(){}
	  virtual ~ApplicationMode(){}
	  virtual void Render(SDL_Renderer *renderer){}
	  virtual void Update(float deltaTime){}
	  virtual void Event(SDL_Event e){}
	  virtual void LoadContent(SDL_Renderer *renderer){}
	  virtual void UnloadContent(){}
};