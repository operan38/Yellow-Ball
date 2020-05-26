#include "Player.h"

Player::Player(ApplicationSettings *appSettings, HUD *hud, std::string name, GameContent *gameContent, int x, int y, int w, int h, int z_index) :Object(name, gameContent->getTexture("Player"), x, y, w, h, z_index)
{
	this->appSettings = appSettings;
	this->hud = hud;
	this->gameContent = gameContent;
	if (appSettings->getTheme() == "Winter") sprNewYearHats = new Sprite(gameContent->getTexture("NewYearHat"), x, y, 40, 40);
	dx = 0; dy = 0; speed = 5;
	health = 100; money = 0;
	isRightButton = false; isLeftButton = false;
	isUpButton = false; isDownButton = false;
	sprite->setAnim(2, 2, 100, true);
	hud->getSpriteHealth()->setCurrentFrameKit(1, false);
}

Player::~Player()
{
	delete sprNewYearHats;
}

void Player::Move(int dx, int dy)
{
	sprite->setPosition(sprite->getX() + dx, sprite->getY() + dy);
}

void Player::Draw(SDL_Renderer *renderer)
{
	Object::Draw(renderer);
	if (appSettings->getTheme() == "Winter") sprNewYearHats->draw(renderer);
}

void Player::Update(float deltaTime)
{
	Move(dx, dy);
	if (appSettings->getTheme() == "Winter") sprNewYearHats->setPosition(sprite->getX(), sprite->getY()-30);
	hud->setHealth(health);
	hud->setMoney(money);
	if (health <= 0)
		isLife = false;

	if (sprite->getCurrentFrameKit() == 1)
	{
		if (sprite->getCurrentFrame() == 1)
			sprite->setFrameSpeed(1200);
		else if (sprite->getCurrentFrame() == 2)
			sprite->setFrameSpeed(100);
	}

	Object::Update(deltaTime);
}

void Player::CheckCollision(Object *object)
{
	if (object->getName() == "Block" && object->getLife()){
		//std::cout << "(Player:) Collision Block" << std::endl;
		if (dx > 0){
			sprite->setX(object->getSprite()->getX() - object->getSprite()->getW());

			if (appSettings->getTheme() == "Winter")
				sprNewYearHats->setPosition(sprite->getX(), sprite->getY() - 30);
		}
		else if (dx < 0){
			sprite->setX(object->getSprite()->getX() + object->getSprite()->getW());

			if (appSettings->getTheme() == "Winter")
				sprNewYearHats->setPosition(sprite->getX(), sprite->getY() - 30);
		}
		if (dy > 0){
			sprite->setY(object->getSprite()->getY() - object->getSprite()->getH());

			if (appSettings->getTheme() == "Winter")
				sprNewYearHats->setPosition(sprite->getX(), sprite->getY() - 30);
		}
		else if (dy < 0){
			sprite->setY(object->getSprite()->getY() + object->getSprite()->getH());

			if (appSettings->getTheme() == "Winter")
				sprNewYearHats->setPosition(sprite->getX(), sprite->getY() - 30);
		}
	}
	if (object->getName() == "BronzeCoin" && object->getLife()){
		//std::cout << "(Player:) Collision BronzeCoin" << std::endl;
		money++;
		object->setLife(false);
		//std::cout << "(Player:) Money: " << money << std::endl;
	}
	if (object->getName() == "SilverCoin" && object->getLife()){
		//std::cout << "(Player:) Collision SilverCoin" << std::endl;
		money += 3;
		object->setLife(false);
		//std::cout << "(Player:) Money: " << money << std::endl;
	}
	if (object->getName() == "GoldCoin" && object->getLife()){
		//std::cout << "(Player:) Collision GoldCoin" << std::endl;
		money += 5;
		object->setLife(false);
		//std::cout << "(Player:) Money: " << money << std::endl;
	}
	if (object->getName() == "LevelGo" && object->getLife()){
		if (appSettings->getCurrentLevel() == 1 && money >= 5){
			appSettings->setNextLevel(true);
		}
		else if (appSettings->getCurrentLevel() == 2 && money >= 10){
			appSettings->setNextLevel(true);
		}
		else if (appSettings->getCurrentLevel() == 3 && money >= 15){
			appSettings->setNextLevel(true);
		}
		else if (appSettings->getCurrentLevel() == 4 && money >= 20){
			appSettings->setNextLevel(true);
		}
		else if (appSettings->getCurrentLevel() == 5 && money >= 25){
			appSettings->setNextLevel(true);
		}
		else if (appSettings->getCurrentLevel() == 6 && money >= 30){
			appSettings->setNextLevel(true);
		}
	}
	if (object->getName() == "LevelEnd" && object->getLife()){
		if (appSettings->getCurrentLevel() == 7 && money >= 35){
			if (appSettings->getTheme() == "Winter")
				appSettings->LoadNewYearScreen();
			else
				appSettings->LoadTitleScreen();
		}
	}
	if (object->getName() == "Enemy1" && object->getLife()){
		health -= 1;
		sprite->setCurrentFrameKit(2, false);
		sprite->setCurrentFrameKit(1, true);
	}
	if (object->getName() == "Enemy2" && object->getLife()){
		health -= 5;
		sprite->setCurrentFrameKit(2, false);
		sprite->setCurrentFrameKit(1, true);
	}
	if (object->getLife() && (object->getName() == "Enemy1" || object->getName() == "Enemy2"))
	{
		if (health > 95) hud->getSpriteHealth()->setCurrentFrameKit(1, false);
		else if (health <= 95 && health > 75) hud->getSpriteHealth()->setCurrentFrameKit(2, false);
		else if (health <= 75 && health > 50) hud->getSpriteHealth()->setCurrentFrameKit(3, false);
		else if (health <= 50 && health > 40) hud->getSpriteHealth()->setCurrentFrameKit(4, false);
		else if (health <= 40 && health > 25) hud->getSpriteHealth()->setCurrentFrameKit(5, false);
		else if (health <= 25 && health > 15) hud->getSpriteHealth()->setCurrentFrameKit(6, false);
		else if (health <= 15 && health > 0) hud->getSpriteHealth()->setCurrentFrameKit(7, false);
		else if (health <= 0) hud->getSpriteHealth()->setCurrentFrameKit(8, false);
	}
}

void Player::Event(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: dy -= speed; isUpButton = true; isLeftButton = false; isRightButton = false; dx = 0; break;
		case SDLK_DOWN:  dy += speed; isDownButton = true; isLeftButton = false; isRightButton = false; dx = 0; break;
		case SDLK_LEFT: dx -= speed; isLeftButton = true; isUpButton = false; isDownButton = false; dy = 0; break;
		case SDLK_RIGHT:  dx += speed; isRightButton = true; isUpButton = false; isDownButton = false; dy = 0; break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: if (isUpButton){ dy += speed; isUpButton = false; } break;
		case SDLK_DOWN: if (isDownButton){ dy -= speed; isDownButton = false; } break;
		case SDLK_LEFT:if (isLeftButton){ dx += speed; isLeftButton = false; } break;
		case SDLK_RIGHT: if (isRightButton){ dx -= speed; isRightButton = false; } break;
		}
	}
}