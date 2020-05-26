#include "AnimationText.h"

AnimationText::AnimationText(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, SDL_Renderer *renderer) :Text(str, x, y, r, g, b, a, fontSize, style, renderer)
{
	Init();
}

AnimationText::AnimationText(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, std::string ID, bool isUpdateLoopText, SDL_Renderer *renderer) : Text(str, x, y, r, g, b, a, fontSize, style, ID, isUpdateLoopText, renderer)
{
	Init();
}

AnimationText::~AnimationText(){}

void AnimationText::Init()
{
	isAnimAlpha = false;
	currentAlpha = 255;
	endAlpha = color.a;
	speedAlpha = 0;
	isAnimMove = false;
	currentMoveX = dstrect.x;
	currentMoveY = dstrect.y;
	endMoveX = dstrect.x;
	endMoveY = dstrect.y;
	speedMove = 0;
}

void AnimationText::draw(SDL_Renderer *renderer)
{
	Text::draw(renderer);
}

void AnimationText::update(float deltaTime)
{
	if (isAnimAlpha)
	{
		if (!isUpdateAnimation)
			isUpdateAnimation = true;
		if (currentAlpha <= endAlpha)
		{
			currentAlpha += speedAlpha;
			setColor(color.r, color.b, color.g, currentAlpha);
			if (currentAlpha > endAlpha){
				stopAnimAlpha();
			}
		}
	}
	if (isAnimMove)
	{
		if (!isUpdateAnimation)
			isUpdateAnimation = true;
		if (currentMoveX < endMoveX)
			currentMoveX += speedMove;
		if (endMoveX < currentMoveX)
			currentMoveX -= speedMove;
		if (currentMoveY < endMoveY)
			currentMoveY += speedMove;
		if (endMoveY < currentMoveY)
			currentMoveY -= speedMove;

		setPosition(currentMoveX, currentMoveY);

		if (currentMoveX >= endMoveX - 3 && currentMoveX <= endMoveX + 3 && currentMoveY >= endMoveY - 3 && currentMoveY <= endMoveY){
			stopAnimMove();
		}
	}
	if (!isAnimAlpha && !isAnimMove && isUpdateAnimation){
		isUpdateAnimation = false;
		//std::cout << "(AnimationText): Stop Animation" << std::endl;
	}
}

void AnimationText::setAnimAlpha(int currentAlpha, int speedAlpha)
{
	this->currentAlpha = currentAlpha;
	this->speedAlpha = speedAlpha;
	isAnimAlpha = true;
}

void AnimationText::setAnimMove(int currentMoveX, int currentMoveY, int speedMove)
{
	this->currentMoveX = currentMoveX;
	this->currentMoveY = currentMoveY;
	this->speedMove = speedMove;
	isAnimMove = true;
}

void AnimationText::stopAnimAlpha()
{
	setColor(color.r, color.b, color.g, endAlpha);
	isAnimAlpha = false;
}

void AnimationText::stopAnimMove()
{
	setPosition(endMoveX, endMoveY);
	isAnimMove = false;
}