#pragma once
#include "Loader.h"

class GameContent : public Loader
{
   public:
	  GameContent(ApplicationSettings *appSettings): Loader(appSettings)
	  {
		  this->appSettings = appSettings;
	  }
	 ~GameContent(){}
	 std::vector<std::string> DefaultLoad()
	 {
		 std::vector<std::string> vector;
		 vector.push_back(DTL + "Themes/" + appSettings->getTheme() + "/GameBackground.png");
		 vector.push_back(DTL + "Themes/" + appSettings->getTheme() + "/Block.png");
		 vector.push_back(DTL + "Player.png");
		 vector.push_back(DTL + "BronzeCoin.png");
		 vector.push_back(DTL + "SilverCoin.png");
		 vector.push_back(DTL + "GoldCoin.png");
		 vector.push_back(DTL + "LevelGo.png");
		 vector.push_back(DTL + "LevelEnd.png");
		 vector.push_back(DTL + "Themes/" + appSettings->getTheme() + "/Enemy1.png");
		 vector.push_back(DTL + "Themes/" + appSettings->getTheme() + "/Enemy2.png");
		 vector.push_back(DTL + "Themes/" + appSettings->getTheme() + "/Block.png");
		 vector.push_back(DTL + "Themes/" + appSettings->getTheme() + "/HUDBackground.png");
		 vector.push_back(DTL + "HUDHealth.png");
		 vector.push_back(DTL + "HUDMoney.png");
		 if (appSettings->getTheme() == "Winter"){
			 vector.push_back(DTL + "SnowFlake.png");
			 vector.push_back(DTL + "NewYearHat.png");
		 }
		 return vector;
	 }
	 bool Load(SDL_Renderer *renderer)
	 {
		 std::cout << "(" << appSettings->getAppMode().c_str() << "): Load Content..." << std::endl;
		 vTexturePath = DefaultLoad();
		 for (unsigned int i = 0; i < vTexturePath.size(); i++){
			 vTexture.push_back(LoadTexture((vTexturePath[i]), renderer));
		 }

		 std::cout << "(" << appSettings->getAppMode().c_str() << "): Load Content Complete" << std::endl;
		 return true;
	 }
	 void CheckContent(SDL_Renderer *renderer)
	 {
		 vTexturePathTemp.clear();
		 std::cout << "(" << appSettings->getAppMode().c_str() << "): Check Content..." << std::endl;
		 vTexturePathTemp = DefaultLoad();
		 for (unsigned int i = 0; i < vTexturePathTemp.size(); i++)
		 {
			 if (vTexturePathTemp[i] != vTexturePath[i])
			 {
				 vTexturePath.erase(vTexturePath.begin() + i);
				 vTexturePath.insert(vTexturePath.begin() + i, vTexturePathTemp[i]);
				 SDL_DestroyTexture(vTexture[i]);
				 vTexture.erase(vTexture.begin() + i);
				 vTexture.insert(vTexture.begin() + i, LoadTexture(vTexturePath[i], renderer));
			 }
			 std::cout << vTexturePathTemp[i].c_str() << std::endl;
		 }
		 std::cout << "(" << appSettings->getAppMode().c_str() << "): Check Content Complete" << std::endl;
	 }
	 void UnLoad()
	 {
		 Loader::UnLoad();
	 }
   private:
	   const std::string DTL = "Data/Textures/";
	   ApplicationSettings *appSettings;
};