#pragma once
#include "point.h"
#include <time.h>
#include <Windows.h>
#include <cstdlib>
#if defined(__WIN32__) || defined(_WIN32) || defined(WIN32) || defined(__WINDOWS__) || defined(__TOS_WIN__)
#include <windows.h>
inline void delay(unsigned long ms)
{
	Sleep(ms);
}

#endif 

void mainValidation(int, char*[]);
void robotFunction(world&);
void worldMap(robot&, robot&, world&);
void coinAndOtherDetails(world&);

bool whileGameIsRunning = true;
int cx1, cy1, cx2, cy2, cx3, cy3;
int loopCounter;

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void clearScreen()
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void mainValidation(int argc, char *argv[]) {

	point coin1Pointer, coin2Pointer, coin3Pointer;
	world coinWorld;
	 
	if (argc == 7) {
		//PERFORM  IF THE 6 REQUIRED ARGUMENTS WERE PASSED FROM CONSOLE
		//Arguments were passed in console (Coin Location Coordinates)

		if (isdigit(*argv[1]) && isdigit(*argv[2]) && isdigit(*argv[3])
			&& isdigit(*argv[4]) && isdigit(*argv[5]) && isdigit(*argv[6]))
		{
			cx1 = stoi(argv[1]);
			cy1 = stoi(argv[2]);
			cx2 = stoi(argv[3]);
			cy2 = stoi(argv[4]);
			cx3 = stoi(argv[5]);
			cy3 = stoi(argv[6]);
		}
		else {
			goto exitProgram;
		}			
	}
	else if (argc <=1) {
		//PERFORM  IF NO ARGUMENT WAS PASSED FROM CONSOLE
		//Generate Random Coin Location
		srand(time(NULL));
		for (int i = 0; i < 6; i++)
		{
			switch (i) {
			case 0:
				cx1 = rand() % (0 + 9);
				break;
			case 1:
				cy1 = rand() % (0 + 9);
				break;
			case 2:
				cx2 = rand() % (0 + 9);
				break;
			case 3:
				cy2 = rand() % (0 + 9);
				break;
			case 4:
				cx3 = rand() % (0 + 9);
				break;
			case 5:
				cy3 = rand() % (0 + 9);
				break;
			default:
				break;
			}
		}
	}
	else {
		//PROMPT FOR ERROR AND EXIT
		exitProgram:
		cout << "Error! Invalid Number Arguments" << endl;
		cout << endl << endl;
		exit(0);
	}

	//THEN HERE....IN CASE NO ERROR AT ARGUMENTS
	coin1Pointer.set(cx1, cy1);
	coin2Pointer.set(cx2, cy2);
	coin3Pointer.set(cx3, cy3);

	//store coins locations in the array
	coinWorld.set(0, coin1Pointer.getX(), coin1Pointer.getY());
	coinWorld.set(1, coin2Pointer.getX(), coin2Pointer.getY());
	coinWorld.set(2, coin3Pointer.getX(), coin3Pointer.getY());

	//SET FLAG VALUE FOR ALL COINS TO FALSE;
	coinWorld.coin1Found = coinWorld.coin2Found = coinWorld.coin3Found = false;

	//Call robot
	robotFunction(coinWorld);
}

void robotFunction(world& wPoint) {
	robot robotPointer1;
	robotPointer1.initTop();

	robot robotPointer2;
	robotPointer2.initBottom();

	//Call Map for coin and robot movement
	worldMap(robotPointer1, robotPointer2, wPoint);
}

void coinAndOtherDetails(world& w) {

	//prints necessary details on screen
	w.print();
	//cout << "W  O  R  L  D          M  A  P" << endl;
	cout << "    _      __  ____    ___    __     ___        __  ___  ___     ___ " << endl;
	cout << "   | | /| / / / __ \\  / _ \\  / /    / _ \\      /  |/  / / _ |   / _ \\" << endl;
	cout << "   | |/ |/ / / /_/ / / , _/ / /__  / // /     / /|_/ / / __ |  / ___/" << endl;
	cout << "   |__/|__/  \\____/ /_/|_| /____/ /____/     /_/  /_/ /_/ |_| /_/   " << endl;
	cout << "                                                                   " << endl;

}

void worldMap(robot& robotPointer1, robot& robotPointer2, world& wPoint) {
	int tempX1, tempX2;

	while (whileGameIsRunning){

		//call nececssary details
		coinAndOtherDetails(wPoint);

		//call the map for the world
		wPoint.printMap(robotPointer1.getX(), robotPointer1.getY(), robotPointer2.getX(), robotPointer2.getY());

		//simulate robots movement

		// IF TRUE WILL MOVE FORWARD/REVERSE
		// IF FALSE WILL EITHER CALL ZIG() OR ZAG()
		robotPointer1.forward();
		robotPointer2.reverse();

		robotPointer1.print(wPoint);

		//go through each location
		//if last location is reached, stop game
		if (wPoint.coin1Found == true && wPoint.coin2Found ==true && wPoint.coin3Found == true) 
		{
			//setGame to finish
			whileGameIsRunning = false;
			break;
		}
		else 
		{
			//pauses in between loop (in terms of millisecond)
			delay(111);
			clearScreen();

			//---------- WILL CAPTURE THE ACCURATE VALUE OF X AT THE END OF THE LOOP----------------
			tempX1 = robotPointer1.getX(); tempX2 = robotPointer2.getX();
			//--------------------------------------------------------------------------------------
		}
	}

	//--------- UNDOS/FIXES THE VALUE OF THE X ------------------------------------------------------
	robotPointer1.fix_X(tempX1); robotPointer2.fix_X(tempX2);
	//-----------------------------------------------------------------------------------------------

	robot robotDistance;
	
	//cout << "X1: " << robotPointer1.getX() << ".  X2: " << robotPointer2.getX() << endl;
	cout << endl << "			Manhattan distance between both robots is: " << robotDistance.distance(robotPointer1, robotPointer2) << endl;
	if (robotPointer1 == robotPointer2)
	{
		cout << "			Robot 1 and Robot 2 are in the same coordinates." << endl;
	}
	else
	{
		cout << "			Robot 1 and Robot 2 are not in the same coordinates." << endl;
	}
	
}