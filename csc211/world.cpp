
#include "world.h"


world::world() {
	//constructor
}

world::~world() {
	//destructor
}

void world::print() const {	
	cout << "\nGENERATED COINS LOCATIONS ( X , Y )     >>>>>>     ";
	for (int i = 0; i < 3; i++)
	{		
		for (int row = 0; row < 1; row++)
		{
			for (int col = 0; col < 2; col++)
			{				
				if (col == 0 ) {
					cout << "( " << coinLocation[i][row][col] << " , ";
				}
				else {
					cout << coinLocation[i][row][col] << " ) ";
				}
			}
			
		}
	}
	cout << endl << endl;
}


void world::set(int i, int x, int y) {

	for (int row = 0; row < 1; row++)
	{
		for (int col = 0; col < 2; col++)
		{
			if (col==0)
			{
				coinLocation[i][row][col] = x;
			}
			else if (col == 1) {
				coinLocation[i][row][col] = y;
			}
			
		
		}
	}
	
}

void world::printMap(int x, int y){

	for (int  row = 0; row < 10; row++)
	{
		for (int col = 0; col < 21; col++)
		{					
			//move robot
			if (row == y && (col % 2 == 0) && (col / 2) == x) {
				cout << worldMap[row][col]  << " R ";
			}
			else if ((row == coinLocation[0][0][1] && col % 2 == 0 && (col / 2) == coinLocation[0][0][0]) && !coin1Found) {
				cout << worldMap[row][col] << " * ";
			}
			else if ((row == coinLocation[1][0][1] && col % 2 == 0 && (col / 2) == coinLocation[1][0][0]) && !coin2Found) {
				cout << worldMap[row][col] << " * ";
			}
			else if ((row == coinLocation[2][0][1] && col % 2 == 0 && (col / 2) == coinLocation[2][0][0]) && !coin3Found) {
				cout << worldMap[row][col] << " * ";
			}
			else {
				cout << worldMap[row][col]  << "   ";
			}

			//if coins are found, set flags to TRUE
			if (((row == coinLocation[0][0][1]) && (row == y)) && ((col % 2 == 0) && (col / 2) == x) &&
				(col % 2 == 0) && (col / 2) == coinLocation[0][0][0]) {
				coin1Found = true;
			}
			if (((row == coinLocation[1][0][1]) && (row == y)) && ((col % 2 == 0) && (col / 2) == x) &&
				(col % 2 == 0) && (col / 2) == coinLocation[1][0][0]) {
				coin2Found = true;
			}
			if (((row == coinLocation[2][0][1]) && (row == y)) && ((col % 2 == 0) && (col / 2) == x) &&
				(col % 2 == 0) && (col / 2) == coinLocation[2][0][0]) {
				coin3Found = true;
			}
		}
		cout << endl;
	}
	cout << endl;
}

int world::getCoordinate(int i, int xORy) {
	int result = 0;

	result = coinLocation[i][0][xORy];

	return result;
}