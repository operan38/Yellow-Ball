#include "Level.h"

Level::Level(ApplicationSettings *appSettings, GameContent *gameContent, HUD *hud)
{
	this->appSettings = appSettings;
	this->gameContent = gameContent;
	this->hud = hud;
	map = new Map;

	map->LoadFromFile("Data/Maps/Level" + std::to_string(appSettings->getCurrentLevel()) + ".txt");
	sGameBackground = new Sprite(gameContent->getTexture("GameBackground"), 0, 0, 800, 600);
	sHUDBackground = new Sprite(gameContent->getTexture("HUDBackground"), 0, 0, 800, 30);

	CreateObjectsFromMap();
}

Level::~Level()
{
	delete map;
	delete sHUDBackground;
	delete sGameBackground;
}

void Level::CreateObjectsFromMap()
{
	for (unsigned int i = 0; i < map->fileMap.size(); i++) // y
	{
		for (unsigned int j = 0; j < map->fileMap[i].size(); j++) // x
		{
			if (map->fileMap[i][j].getX() == 1 && map->fileMap[i][j].getY() == 0)
			{
				map->objects.push_back(new Object("Block", gameContent->getTexture("Block"), j * 40, i * 40, 40, 40, 0));
			}
			if (map->fileMap[i][j].getX() == 2 && map->fileMap[i][j].getY() == 0)
			{
				map->objects.push_back(new Player(appSettings, hud, "Player", gameContent, j * 40, i * 40, 80, 80, 2));
			}
			if (map->fileMap[i][j].getX() == 3 && map->fileMap[i][j].getY() == 0)
			{
				map->objects.push_back(new Object("BronzeCoin", gameContent->getTexture("BronzeCoin"), j * 40, i * 40, 40, 40, 0));
			}
			if (map->fileMap[i][j].getX() == 3 && map->fileMap[i][j].getY() == 1)
			{
				map->objects.push_back(new Object("SilverCoin", gameContent->getTexture("SilverCoin"), j * 40, i * 40, 40, 40, 0));
			}
			if (map->fileMap[i][j].getX() == 3 && map->fileMap[i][j].getY() == 2)
			{
				map->objects.push_back(new Object("GoldCoin", gameContent->getTexture("GoldCoin"), j * 40, i * 40, 40, 40, 0));
			}
			if (map->fileMap[i][j].getX() == 4 && map->fileMap[i][j].getY() == 0)
			{
				map->objects.push_back(new Object("LevelGo", gameContent->getTexture("LevelGo"), j * 40, i * 40, 40, 40, 0));
			}
			if (map->fileMap[i][j].getX() == 4 && map->fileMap[i][j].getY() == 1)
			{
				map->objects.push_back(new Object("LevelEnd", gameContent->getTexture("LevelEnd"), j * 40, i * 40, 40, 40, 0));
			}
			if (map->fileMap[i][j].getX() == 5 && map->fileMap[i][j].getY() == 0)
			{
				map->objects.push_back(new Enemy1(appSettings, "Enemy1", gameContent, j * 40, i * 40, 40, 40, 1));
			}
			if (map->fileMap[i][j].getX() == 6 && map->fileMap[i][j].getY() >= 1 && map->fileMap[i][j].getY() <= 4)
			{
				map->objects.push_back(new Enemy2("Enemy2", gameContent->getTexture("Enemy2"), j * 40, i * 40, 40, 40, 1, map->fileMap[i][j].getY()));
			}
		}
	}
    InsertSort(); // z_index сортировка
}

void Level::InsertSort()
{
	Object *obj;
	for (unsigned int i = 1, j; i < map->objects.size(); i++) // цикл проходов, i - номер прохода
	{
		obj = map->objects[i];
		for (j = i - 1; j >= 0 && map->objects[j]->getZIndex() > obj->getZIndex(); j--) // поиск места элемента в готовой последовательности 
			map->objects[j + 1] = map->objects[j];    // сдвигаем элемент направо, пока не дошли

		map->objects[j + 1] = obj; // место найдено, вставить элемент
	}
	obj = nullptr;
}

bool Level::RectCollision(int Ax, int Ay, int Aw, int Ah, int Bx, int By, int Bw, int Bh)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = Ax;
	rightA = Ax + Aw;
	topA = Ay;
	bottomA = Ay + Ah;

	leftB = Bx;
	rightB = Bx + Bw;
	topB = By;
	bottomB = By + Bh;

	if (bottomA <= topB)
		return false;

	if (topA >= bottomB)
		return false;

	if (rightA <= leftB)
		return false;

	if (leftA >= rightB)
		return false;

	return true;
}

void Level::Draw(SDL_Renderer *renderer)
{
	sGameBackground->draw(renderer);
	for (unsigned int i = 0; i < map->objects.size(); i++)
		 map->objects[i]->Draw(renderer);

	sHUDBackground->draw(renderer);
}

void Level::Update(float deltaTime)
{
	for (unsigned int i = 0; i < map->objects.size(); i++)
	{
		map->objects[i]->Update(deltaTime);
		if (!map->objects[i]->getLife())
			 map->objects.erase(map->objects.begin() + i);
	}
	for (unsigned int i = 0; i < map->objects.size(); i++)
	{
		for (unsigned int j = 0; j < map->objects.size(); j++)
		{
			if (RectCollision(map->objects[i]->getSprite()->getX(), map->objects[i]->getSprite()->getY(), map->objects[i]->getSprite()->getW(), map->objects[i]->getSprite()->getH(),
				              map->objects[j]->getSprite()->getX(), map->objects[j]->getSprite()->getY(), map->objects[j]->getSprite()->getW(), map->objects[j]->getSprite()->getH()))
			{
				map->objects[i]->CheckCollision(map->objects[j]);
			}
		}
	}
}

void Level::Event(SDL_Event e)
{
	for (unsigned int i = 0; i < map->objects.size(); i++)
		 map->objects[i]->Event(e);
}