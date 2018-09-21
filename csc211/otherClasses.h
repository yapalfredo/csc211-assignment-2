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
void worldMap(robot&, world&);
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
	robot robotPointer;

	robotPointer.init();

	//Call Map for coin and robot movement
	worldMap(robotPointer, wPoint);
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

void worldMap(robot& robotPointer, world& wPoint) {
	loopCounter = 0;

	while (whileGameIsRunning) {

		//call nececssary details
		coinAndOtherDetails(wPoint);

		//call the map for the world
		wPoint.printMap(robotPointer.getX(), robotPointer.getY());

		//simulate robot's movement
		// IF TRUE WILL MOVE FORWARD
		// IF FALSE WILL EITHER CALL ZIG() OR ZAG()
		robotPointer.forward();

		robotPointer.print(wPoint);

		//go through each location
		//if last location is reached, stop game
		if ((robotPointer.getX() == 0 && robotPointer.getY() == 9) || 
			(wPoint.coin1Found == true && wPoint.coin2Found ==true && wPoint.coin3Found == true)) {
			
			if (wPoint.coin1Found == false && wPoint.coin2Found==false && wPoint.coin3Found == false) {
				delay(111);
				clearScreen();
				//recalls when last end of mapped is reached
				coinAndOtherDetails(wPoint);
				wPoint.printMap(robotPointer.getX(), robotPointer.getY());
				robotPointer.print();
			}
			//setGame to finish
			whileGameIsRunning = false;
		}
		else {
			//pauses in between loop (in terms of millisecond)
			delay(111);
			clearScreen();
		}
		loopCounter++;
	}
	cout << endl << "				Robot found all coins. It took "<< 
		loopCounter <<" movements in total." << endl;
}