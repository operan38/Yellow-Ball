#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

class Text
{
    public:
	  Text(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, SDL_Renderer *renderer);
	  Text(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, std::string ID, bool isUpdateLoopText, SDL_Renderer *renderer);
	  virtual ~Text();
	  void draw(SDL_Renderer *renderer);
	  void update(float deltaTime);
	  void setPosition(int x, int y);
	  SDL_Rect getPosition();
	  void setString(std::wstring str);
	  std::wstring getString();
	  void setColor(int r, int g, int b, int a);
	  SDL_Color getColor();
	  void setID(std::string ID);
	  std::string getID();
	  void setUpdateLoopText(bool isUpdateLoopText);
	  bool getUpdateLoopText();
    protected:
		void CreateTextureFromSurface(SDL_Renderer *renderer);
		void UpdateText(SDL_Renderer *renderer);
		bool isUpdateLoopText,isUpdateAnimation,isOneUpdateText;
		std::string ID;
		std::wstring str;
		SDL_Surface *loadedSurface;
		SDL_Texture *texture;
		SDL_Rect dstrect;
		SDL_Color color;
		TTF_Font *font;
    private:
	    void Init(const std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, std::string ID, bool isUpdateLoopText, SDL_Renderer *renderer);
};