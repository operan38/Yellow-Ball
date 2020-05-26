#pragma once
#include "Text.h"

class AnimationText : public Text
{
   public:
	 AnimationText(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, SDL_Renderer *renderer);
	 AnimationText(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, std::string ID, bool isUpdateLoopText, SDL_Renderer *renderer);
	 ~AnimationText();
	 void draw(SDL_Renderer *renderer);
	 void update(float deltaTime);
	 bool getAnimMove(){ return isAnimMove; }
	 void setAnimMove(int currentMoveX, int currentMoveY, int speedMove);
	 void setAnimAlpha(int currentAlpha, int speedAlpha);
	 void stopAnimMove();
	 void stopAnimAlpha();
   private:
	   void Init();
	   bool isAnimAlpha;
	   int currentAlpha, endAlpha, speedAlpha;
	   bool isAnimMove;
	   int speedMove;
	   int currentMoveX, currentMoveY, endMoveX, endMoveY;
};