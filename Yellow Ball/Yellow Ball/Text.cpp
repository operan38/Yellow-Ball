#include "Text.h"

Text::Text(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, SDL_Renderer *renderer)
{
	ID = "";
	isUpdateLoopText = false;
	Init(str, x, y, r, g, b, a, fontSize, style, ID, isUpdateLoopText, renderer);
	CreateTextureFromSurface(renderer);
}

Text::Text(std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, std::string ID, bool isUpdateLoopText, SDL_Renderer *renderer)
{
	this->ID = ID;
	this->isUpdateLoopText = isUpdateLoopText;
	Init(str, x, y, r, g, b, a, fontSize, style, ID, isUpdateLoopText, renderer);
	CreateTextureFromSurface(renderer);
}

Text::~Text()
{
	if (font != nullptr)
		TTF_CloseFont(font);
	if (texture != nullptr)
	    SDL_DestroyTexture(texture);
	if (loadedSurface != nullptr)
	    SDL_FreeSurface(loadedSurface);
}

void Text::Init(const std::wstring str, int x, int y, int r, int g, int b, int a, int fontSize, int style, std::string ID, bool isUpdateLoopText, SDL_Renderer *renderer)
{
	font = TTF_OpenFont("Data/verdana.ttf", fontSize);
	TTF_SetFontStyle(font, style);
	loadedSurface = nullptr;
	texture = nullptr;
	this->str = str;
	dstrect.x = x;
	dstrect.y = y;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	isOneUpdateText = false;
	isUpdateAnimation = false;
	std::vector<Uint16> uint16_str(str.length() + 1);
	std::copy(str.begin(), str.end(), uint16_str.begin());
	loadedSurface = TTF_RenderUNICODE_Blended(font, uint16_str.data(), color);
}

void Text::draw(SDL_Renderer* renderer)
{
	if (isUpdateLoopText){
		UpdateText(renderer);
	}
	if (isUpdateAnimation && !isUpdateLoopText){
		UpdateText(renderer);
	}

	if (!isUpdateLoopText && !isUpdateAnimation)
	{
		if (isOneUpdateText)
		{
			UpdateText(renderer);
			isOneUpdateText = false;
		}
	}
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
}

void Text::update(float deltaTime){}

void Text::CreateTextureFromSurface(SDL_Renderer *renderer)
{
	dstrect.w = loadedSurface->w;
	dstrect.h = loadedSurface->h;
	if (loadedSurface == nullptr)
		std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;
	else{
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (color.a != 255)
		    SDL_SetTextureAlphaMod(texture, color.a);

		if (texture == nullptr)
			std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;
	}
}

void Text::UpdateText(SDL_Renderer *renderer)
{
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(loadedSurface);
	std::vector<Uint16> uint16_str(str.length() + 1);
	std::copy(str.begin(), str.end(), uint16_str.begin());
	loadedSurface = TTF_RenderUNICODE_Blended(font, uint16_str.data(), color);
	CreateTextureFromSurface(renderer);
}

void Text::setPosition(int x, int y)
{
	dstrect.x = x;
	dstrect.y = y;
}

void Text::setString(std::wstring str)
{
	this->str = str;

	if (!isUpdateLoopText && !isUpdateAnimation)
		isOneUpdateText = true;
}

std::wstring Text::getString()
{
	return str;
}

void Text::setID(std::string ID)
{
	this->ID = ID;
}

std::string Text::getID()
{
	return ID;
}

void Text::setUpdateLoopText(bool isUpdateLoopText)
{
	this->isUpdateLoopText = isUpdateLoopText;
}

bool Text::getUpdateLoopText()
{
	return isUpdateLoopText;
}

void Text::setColor(int r, int g, int b, int a)
{
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;

	if (!isUpdateLoopText && !isUpdateAnimation)
		isOneUpdateText = true;
}

SDL_Color Text::getColor()
{
	return color;
}