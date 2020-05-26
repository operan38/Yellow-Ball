#pragma once
#include <iostream>
#include <fstream>

class ApplicationSettings
{
   public:
	 ApplicationSettings() :APP_MODE("TitleScreen"), APP_PAUSE(false), APP_MODE_CHANGE(false), isDebug(false), isExit(false), isNextLevel(false), currentLevel(1), maxLevel(1), theme("Winter")
	 {
		 LoadSettings();
	 }
	 ~ApplicationSettings(){}
	 bool SaveSettings()
	 {
		 std::cout << "(AppSettings): Save Settings..." << std::endl;
		 std::ofstream openfile;
		 openfile.open("Data/Settings.txt");
		 openfile.clear();
		 if (openfile.is_open() && !openfile.eof())
		 {
			 openfile << maxLevel;
			 std::cout << "(AppSettings): Save Settings Complete" << std::endl;
		 }
		 else{
			 return false;
		 }
		 openfile.close();
		 return true;
	 }
	 bool LoadSettings()
	 {
		 std::cout << "(AppSettings): Load Settings..." << std::endl;
		 std::ifstream openfile;
		 openfile.open("Data/Settings.txt");
		 if (openfile.is_open() && !openfile.eof())
		 {
			 int line;
			 int i = 0;
			 while (!openfile.eof())
			 {
				 openfile >> line;
				 if (i == 0){ if (line >= 1 && line <= 7) maxLevel = line; }
				 i++;
			 }
			 std::cout << "(AppSettings): Load Settings Complete" << std::endl;
		 }
		 else{
			 return false;
		 }
		 openfile.close();
		 return true;
	 }
	 std::string getAppMode(){ return APP_MODE; }
	 void setAppPause(bool APP_PAUSE){ this->APP_PAUSE = APP_PAUSE; }
	 bool getAppPause(){ return APP_PAUSE; }
	 void setDebug(bool isDebug){ this->isDebug = isDebug; }
	 bool getDebug(){ return isDebug; }
	 void setMaxLevel(int maxLevel){ this->maxLevel = maxLevel; }
	 int getMaxLevel(){ return maxLevel; }
	 void setCurrentLevel(int currentLevel){ this->currentLevel = currentLevel; }
	 int getCurrentLevel(){ return currentLevel; }
	 std::string getTheme(){ return theme; }
	 void setThemeStandard(){ theme = "Standard"; }
	 void setThemeWinter(){ theme = "Winter"; }
	 bool getExit(){ return isExit; }
	 void setExit(bool isExit){ SaveSettings(); this->isExit = isExit; }
	 bool getNextLevel(){ return isNextLevel; }
	 void setNextLevel(bool isNextLevel){ this->isNextLevel = isNextLevel; }
	 bool getAppModeChange(){ return APP_MODE_CHANGE; }
	 void setAppModeChange(bool APP_MODE_CHANGE){ this->APP_MODE_CHANGE = APP_MODE_CHANGE; }
	 void LoadTitleScreen(){ APP_MODE = "TitleScreen"; APP_MODE_CHANGE = true; }
	 void LoadGameScreen(){ APP_MODE = "GameScreen"; APP_MODE_CHANGE = true; }
	 void LoadNewYearScreen(){ APP_MODE = "NewYearScreen"; APP_MODE_CHANGE = true; }
   private:
	   std::string APP_MODE;
	   bool APP_PAUSE, APP_MODE_CHANGE, isDebug, isExit, isNextLevel;
	   int maxLevel;
	   int currentLevel;
	   std::string theme;
};