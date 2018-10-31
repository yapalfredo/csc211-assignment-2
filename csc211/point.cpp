#include "point.h"

point::point() {
	// constructor
}

point::~point() {
	// destructor
}


void point::print()const {
	cout << " x is at: " << getX() << endl;
	cout << " y is at: " << getY() <<endl;
}

void point::set(int x, int y) {
	if ((x >= 0 && x <= 9) && (y >= 0 && y <= 9)) {
		this->x = x;
		this->y = y;
	}
	else {
		cout << "Error! Invalid Number Arguments" << endl;
		cout << endl << endl;
		exit(0);
	}
}

int point::getX() const{
	return x;
}

int point::getY() const{
	return y;
}

void point::setX(int x) {
	this->x = x;
}
void point::setY(int y) {
	this->y = y;
}

point point::operator++(int)
{
	this->setX(this->getX() + 1);

	return *this;
}

point point::operator--(int)
{
	this->setX(this->getX() - 1);

	return *this;
}