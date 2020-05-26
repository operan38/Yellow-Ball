#pragma once
#include "Loader.h"

class TitleContent : public Loader
{
   public:
	  TitleContent(ApplicationSettings *appSettings) :Loader(appSettings)
	  {
		  this->appSettings = appSettings;
	  }
	 ~TitleContent(){}
	 bool Load(SDL_Renderer *renderer)
	 {
		 std::cout << "(" << appSettings->getAppMode().c_str() << "): Load Content..." << std::endl;
		 vTexturePath.push_back(DTL + "Themes/" + appSettings->getTheme() + "/TitleBackground.png");
		 vTexturePath.push_back(DTL + "Themes/" + appSettings->getTheme() + "/TitleText.png");
		 vTexturePath.push_back(DTL + "Button.png");
		 for (unsigned int i = 0; i < vTexturePath.size(); i++){
			 vTexture.push_back(LoadTexture((vTexturePath[i]), renderer));
		 }

		 std::cout << "(" << appSettings->getAppMode().c_str() << "): Load Content Complete" << std::endl;
		 return true;
	 }
	 void UnLoad()
	 {
		 Loader::UnLoad();
	 }
   private:
	   const std::string DTL = "Data/Textures/";
	   ApplicationSettings *appSettings;
};