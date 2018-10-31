#include "robot.h"

robot::robot() {
	//constructor
	posOfRobot.set(0, 0);
}

//constructor with point
robot::robot(point robotPoint) {
	posOfRobot.set(robotPoint.getX(), robotPoint.getY());
}

//contructor with name and point
robot::robot(string name, point robotPoint) {
	posOfRobot.set(robotPoint.getX(), robotPoint.getY());
	this->name = name;
}

robot::~robot() {
	//destructor
}

void robot::initTop() {
	posOfRobot.set(0, 0);
	setOrientation(east);
}

void robot::initBottom() {
	posOfRobot.set(9, 9);
	setOrientation(west);
}

void robot::setOrientation(orientation_type orientation) {
	this->orientation = orientation;
}

int robot::getX() {
	return posOfRobot.getX();
}

int robot::getY() {
	return posOfRobot.getY();
}

void robot::print() const {

	cout << "Robot's moving and searching for coin....." << endl << endl;
	cout << "Robot's location is at (" << posOfRobot.getX() << "," << posOfRobot.getY() << ") and facing ";
	switch (orientation)
	{
	case robot::east:
		cout << " E A S T.        " << endl;
		break;
	case robot::west:
		cout << " W E S T.       " << endl;
		break;
	case robot::south:
		cout << " S O U T H.      " << endl;
		break;
	case robot::north:
		cout << " N O R T H.       " << endl;
		break;
	default:
		break;
	}
}

void robot::print(world& w) const {
	cout << endl << "P R O G R E S S:" << endl;
	string a, b, c;
	
	int counter = 0;
	
	// PROGRESS MESSAGE
	string message[3];
	if (w.coin1Found) {
		message[counter] = "		found a coin at (" + to_string(w.getCoordinate(0, 0))+ "," + to_string(w.getCoordinate(0, 1))+ ") YEHEY!!! ";
		counter+=1;
	}if (w.coin2Found) {
		message[counter] = "		found a coin at (" + to_string(w.getCoordinate(1, 0)) + "," + to_string(w.getCoordinate(1, 1)) + ") YEHEY!!! ";
		counter+=1;
	} if (w.coin3Found) {
		message[counter] = "		found a coin at (" + to_string(w.getCoordinate(2, 0)) + "," + to_string(w.getCoordinate(2, 1)) + ") YEHEY!!! ";
		counter+=1;
	}
	
	for (int i = 0; i <counter; i++)
	{
		if (counter == 1) {
			cout << message[i] << endl;
		}
		else {
			cout << message[counter - 1 - i] << endl;
		}
	}

}

bool robot::eastEnd() {
	bool result;

	if (posOfRobot.getX() >= 9) {
		result = true;
	}
	else {
		result = false;
	}
	return result;
}

bool robot::westEnd() {
	bool result;

	if (posOfRobot.getX() <= 0) {
		result = true;
	}
	else {
		result = false;
	}
	return result;
}

bool robot::southEnd() {
	bool result;

	if (posOfRobot.getY() > 9) {
		result = true;
	}
	else {
		result = false;
	}
	return result;
}

bool robot::northEnd() {
	bool result;

	if (posOfRobot.getY() < 0) {
		result = true;
	}
	else {
		result = false;
	}
	return result;
}

void robot::turnCW(char i) {

	print();

	switch (i)
	{
	case 'f':
		if (orientation == east) {
			setOrientation(south);
			posOfRobot.setY(posOfRobot.getY() + 1);
		}
		else if (orientation == south) {
			setOrientation(west);
		}
		break;
	case 'r':
		if (orientation == east) {
			setOrientation(north);
			posOfRobot.setY(posOfRobot.getY() - 1);
		}
		else if (orientation == north) {
			setOrientation(west);
		}
		break;
	default:
		break;
	}

}

void robot::turnAntiCW(char i) {

	print();

	switch (i)
	{
	case 'f':
		if (orientation == west) {
			setOrientation(south);
			posOfRobot.setY(posOfRobot.getY() + 1);
		}
		else if (orientation == south) {
			setOrientation(east);
		}
		break;
	case 'r':
		if (orientation == west) {
			setOrientation(north);
			posOfRobot.setY(posOfRobot.getY() - 1);
		}
		else if (orientation == north) {
			setOrientation(east);
		}
		break;
	default:
		break;
	}
}

bool robot::forward() {
	bool result = true;

	if (orientation == east && !(eastEnd())) {
		print();
		//Operator++ Overloading (increments x-coordinate)
		posOfRobot++;
	}
	else if (orientation == west && !(westEnd())) {
		print();
		//Operator-- Overloading (decrements x-coordinate)
		posOfRobot--;
	}
	else {
		//FALSE AREA
		if (eastEnd() && (zag('f'))) {
			//face south then west
		}
		else if (westEnd() && zig('f')) {
			//face south then east
		}
		result = false;
	}
	return result;
}

bool robot::reverse() {
	bool result = true;

	if (orientation == east && !(eastEnd())) {
		print();
		//Operator++ Overloading (increments x-coordinate)
		posOfRobot++;
	}
	else if (orientation == west && !(westEnd())) {
		print();
		//Operator-- Overloading (decrements x-coordinate)
		posOfRobot--;
	}
	else {
		//FALSE AREA
		if (eastEnd() && (zag('r'))) {
			//face north then west
		}
		else if (westEnd() && zig('r')) {
			//face north then east
		}
		result = false;
	}
	return result;
}

bool robot::zag(char i) {
	bool result = true;

	switch (i)
	{
	case 'f':
		if (orientation == east || orientation == south) 
		{
			turnCW('f');
		}
		break;
	case 'r':
		if (orientation == east || orientation == north)
		{
			turnCW('r');
		}
		break;
	default:
		break;
	}
	
	return result;
}

bool robot::zig(char i) {
	bool result = true;

	switch (i)
	{
	case 'f':
		if (orientation == west || orientation == south) {
			turnAntiCW('f');
		}
		else {
			result = false;
		}
		break;
	case 'r':
		if (orientation == west || orientation == north) {
			turnAntiCW('r');
		}
		else {
			result = false;
		}
		break;
	default:
		break;
	}

	return result;
}