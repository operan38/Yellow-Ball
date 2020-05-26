#include "AnimationSprite.h"

AnimationSprite::AnimationSprite(SDL_Texture *texture, int x, int y, int w, int h) :Sprite(texture, x, y, w, h)
{
	isAnim = false;
	isAnimLoop = false;
	originRect.x = 0;
	originRect.y = 0;
	originRect.w = 0;
	originRect.h = 0;
}

AnimationSprite::~AnimationSprite()
{
	delete frameTimer;
}

void AnimationSprite::draw(SDL_Renderer *renderer)
{
	Sprite::draw(renderer);
}

void AnimationSprite::update(float deltaTime)
{
	if (isAnim)
	{
		if (isAnimLoop)
		{
			if (currentFrame == frameCount && frameTimer->getTicks() >= frameSpeed)
			{
				frameTimer->start();
				currentFrame = 1;
				setTextureRect(originRect.w*currentFrameKit - originRect.w, originRect.h*currentFrame - originRect.h, originRect.w, originRect.h);
			}
			else if (frameTimer->getTicks() >= frameSpeed)
			{
				frameTimer->start();
				setTextureRect(originRect.w*currentFrameKit - originRect.w, originRect.h*currentFrame, originRect.w, originRect.h);
				currentFrame++;
			}
		}
		else
		{
			if (currentFrame == frameCount && frameTimer->getTicks() >= frameSpeed)
			{
				isAnim = false;
				frameTimer->stop();
			}
			else if (frameTimer->getTicks() >= frameSpeed)
			{
				frameTimer->start();
				setTextureRect(originRect.w*currentFrameKit - originRect.w, originRect.h*currentFrame, originRect.w, originRect.h);
				currentFrame++;
			}
		}
	}
}

void AnimationSprite::setCurrentFrameKit(Uint32 currentFrameKit, bool isWatingChangeFrame)
{
	if (this->currentFrameKit != currentFrameKit)
	{
		this->currentFrameKit = currentFrameKit;

		if (!isAnimLoop || !isWatingChangeFrame)
			setTextureRect(originRect.w*currentFrameKit - originRect.w, originRect.y, originRect.w, originRect.h);
	}
}

void AnimationSprite::setCurrentFrame(Uint32 currentFrame, bool isWatingChangeFrame)
{
	if (this->currentFrame != currentFrame)
	{
		this->currentFrame = currentFrame;

		if (!isAnimLoop || !isWatingChangeFrame)
			setTextureRect(originRect.w*currentFrameKit - originRect.w, originRect.h*currentFrame - originRect.h, originRect.w, originRect.h);
	}
}

void AnimationSprite::setFrameKitCount(Uint32 frameKitCount)
{
	this->frameKitCount = frameKitCount;
	currentFrameKit = 1;
}

void AnimationSprite::setFrameSpeed(Uint32 frameSpeed)
{
	if (this->frameSpeed != frameSpeed)
		this->frameSpeed = frameSpeed;
}

Uint32 AnimationSprite::getFrameSpeed()
{
	return frameSpeed;
}

Uint32 AnimationSprite::getCurrentFrame()
{
	return currentFrame;
}

Uint32 AnimationSprite::getCurrentFrameKit()
{
	return currentFrameKit;
}

void AnimationSprite::setAnim(Uint32 frameCount, Uint32 frameKitCount, Uint32 frameSpeed, bool isAnimLoop)
{
	this->frameCount = frameCount;
	this->frameKitCount = frameKitCount;
	this->frameSpeed = frameSpeed;
	this->isAnimLoop = isAnimLoop;

	currentFrame = 1;
	currentFrameKit = 1;

	if (originRect.w == 0 || originRect.h == 0)
	{
		originRect.x = 0;
		originRect.y = 0;
		originRect.w = dstRect.w / frameKitCount;
		originRect.h = dstRect.h / frameCount;
	}

	setTextureRect(originRect.w*currentFrameKit - originRect.w, originRect.h*currentFrame - originRect.h, originRect.w, originRect.h);

	isAnim = true;

    frameTimer = new Timer;
    frameTimer->start();
}

bool AnimationSprite::getAnim()
{
	return isAnim;
}

void AnimationSprite::resumeAnim()
{
	frameTimer->unpause();
}

void AnimationSprite::pauseAnim()
{
	frameTimer->pause();
}

void AnimationSprite::restartAnim()
{
	currentFrame = 1;
	currentFrameKit = 1;
	frameTimer->start();
}

void AnimationSprite::stopAnim()
{
	isAnimLoop = false;
	isAnim = false;
	currentFrame = frameCount-1;
	frameTimer->stop();
	setTextureRect(originRect.w*currentFrameKit - originRect.w, originRect.h*currentFrame - originRect.h, originRect.w, originRect.h);
}