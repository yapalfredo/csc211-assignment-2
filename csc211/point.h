#pragma once
#include <iostream>
#include <string>

using namespace std;

class point{
  private:
	  int  x, y;
  public:

    point();
    ~point();

	void print() const;
    //mutator
	void set(int, int);
	void setX(int);
	void setY(int);

    //accessor
	int getX() const;
	int getY() const;

	//operatorOverloading
	point operator++(int);
	point operator--(int);

};