#pragma once
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Vector2i.h"
#include "Object.h"

class Map
{
    public:
	   Map(){}
	  ~Map()
	  {
		  fileMap.clear();
		  for (std::vector<Object*>::iterator i = objects.begin(); i != objects.end(); i++)
			  delete (*i);
		  std::vector<Object*>().swap(objects);
	  }
	  void LoadFromFile(std::string fileName)
	  {
		  std::cout << "(Map): LoadFromFile (" << fileName << ")" << std::endl;
		  std::ifstream openfile;
		  openfile.open(fileName);

		  if (openfile.is_open() && !openfile.eof())
		  {
			  std::string str;
			  while (!openfile.eof())
			  {
				  std::getline(openfile, str);
				  std::stringstream stream(str);
				  std::string value;

				  while (std::getline(stream, value, ' '))
				  {
					  if (value.length() > 0)
					  {
						  std::string x = value.substr(0, value.find(','));
						  std::string y = value.substr(value.find(',') + 1);

						  tempMap.push_back(Vector2i(stoi(x), stoi(y)));
					  }
				  }
				  fileMap.push_back(tempMap);
				  tempMap.clear();
			  }
		  }
		  else
			  std::cout << "(Map): Not Found or Error" << std::endl;

		  openfile.close();

		  /*for (unsigned int i = 0; i < fileMap.size(); i++){
		  for (unsigned int j = 0; j < fileMap[i].size(); j++){
		  std::cout << fileMap[i][j].getX();
		  std::cout << fileMap[i][j].getY();
		  std::cout << ",";
		  }
		  std::cout << std::endl;
		  }*/
	  }
	  std::vector<std::vector<Vector2i>> fileMap;
	  std::vector<Object*> objects;
    private:
		std::vector<Vector2i> tempMap;
};