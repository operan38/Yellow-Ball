#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "ApplicationSettings.h"

class Loader
{
   public:
	 Loader(){}
	 Loader(ApplicationSettings *appSettings)
	 {
		 this->appSettings = appSettings;
	 }
	 virtual ~Loader(){}
	 SDL_Texture *getTexture(std::string ID)
	 {
		 for (unsigned int i = 0; i < vTexturePath.size(); i++)
		 {
			 if (vTexturePath[i] == DTL + ID + ".png")
			 {
				 return vTexture[i];
			 }
			 else if (vTexturePath[i] == DTL + "Themes/" + appSettings->getTheme() + "/" + ID + ".png")
			 {
				 return vTexture[i];
			 }
		 }
		 return vTexture[0];
	 }
   protected:
	 SDL_Texture *LoadTexture(std::string file, SDL_Renderer *renderer)
	 {
		 SDL_Texture *newTexture = nullptr;

		 SDL_Surface *loadedSurface = IMG_Load(file.c_str());

		 if (loadedSurface == nullptr){
			 std::cout << "Unable to load the image " << file.c_str() << std::endl << "SDL_Image Error: " << IMG_GetError() << std::endl;
		 }
		 else
		 {
			 newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
			 if (newTexture == nullptr)
				 std::cout << "Unable to create the texture from " << file.c_str() << std::endl << "SDL Error: " << SDL_GetError() << std::endl;

			 SDL_FreeSurface(loadedSurface);
		 }

		 return newTexture;
	 }
	 virtual void UnLoad()
	 {
		 std::cout << "UnLoad Content..." << std::endl;

		 for (unsigned int i = 0; i < vTexture.size(); i++)
			 SDL_DestroyTexture(vTexture[i]);

		 std::vector<SDL_Texture*>().swap(vTexture);
		 vTexturePath.clear();
		 vTexturePathTemp.clear();

		 std::cout << "UnLoad Content Complete" << std::endl;
	 }
	 std::vector<SDL_Texture*> vTexture;
	 std::vector<std::string> vTexturePath;
	 std::vector<std::string> vTexturePathTemp;
   private:
	   const std::string DTL = "Data/Textures/";
	   ApplicationSettings *appSettings;
};