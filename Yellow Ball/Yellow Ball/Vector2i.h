#pragma once

class Vector2i
{
    public:
	  Vector2i(){}
	  Vector2i(int x, int y)
	  {
		  this->x = x;
		  this->y = y;
	  }
	  ~Vector2i(){}

	  int getX(){ return x; }
	  int getY(){ return y; }
	  void setX(int x){ this->x = x; }
	  void setY(int y){ this->y = y; }
    private:
		int x, y;
};