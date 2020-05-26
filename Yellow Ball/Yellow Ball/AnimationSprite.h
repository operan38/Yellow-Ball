#pragma once
#include "Sprite.h"
#include "Timer.h"

class AnimationSprite : public Sprite
{
    public:
	  AnimationSprite(SDL_Texture *texture, int x, int y, int w, int h);
	  ~AnimationSprite();
	  void draw(SDL_Renderer *renderer);
	  void update(float deltaTime);
	  void setAnim(Uint32 frameCount, Uint32 frameKitCount, Uint32 frameSpeed, bool isAnimLoop);
	  void resumeAnim();
	  void pauseAnim();
	  void restartAnim();
	  void stopAnim();
	  void setFrameKitCount(Uint32 frameKitCount);
	  void setCurrentFrameKit(Uint32 currentFrameKit, bool isWatingChangeFrame);
	  void setCurrentFrame(Uint32 currentFrame, bool isWatingChangeFrame);
	  void setFrameSpeed(Uint32 frameSpeed);
	  bool getAnim();
	  Uint32 getFrameSpeed();
	  Uint32 getCurrentFrameKit();
	  Uint32 getCurrentFrame();
    private:
		SDL_Rect originRect;
		Uint32 frameSpeed;
		Uint32 currentFrame, frameCount, currentFrameKit, frameKitCount;
		bool isAnim;
		bool isAnimLoop;
		Timer *frameTimer;
};