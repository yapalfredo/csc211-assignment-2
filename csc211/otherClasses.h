#pragma once
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

void coinFunction();
void robotFunction(world&);
void worldMap(robot&, world&);
void coinAndOtherDetails(world&);

bool whileGameIsRunning = true;


int cx1, cy1, cx2, cy2, cx3, cy3;

void coinFunction() {

	point coin1Pointer, coin2Pointer, coin3Pointer;
	world coinWorld;

	srand(time(NULL));
	for (size_t i = 0; i < 6; i++)
	{
		if (i == 0)
		{
			cx1 = rand() % (0 + 9);
		}
		else if (i == 1)
		{
			cy1 = rand() % (0 + 9);
		}
		else if (i == 2)
		{
			cx2 = rand() % (0 + 9);
		}
		else if (i == 3)
		{
			cy2 = rand() % (0 + 9);
		}
		else if (i == 4)
		{
			cx3 = rand() % (0 + 9);
		}
		else if (i == 5)
		{
			cy3 = rand() % (0 + 9);
		}
	}

	coin1Pointer.set(cx1, cy1);
	coin2Pointer.set(cx2, cy2);
	coin3Pointer.set(cx3, cy3);

	//store coins locations in the array
	coinWorld.set(0, coin1Pointer.getX(), coin1Pointer.getY());
	coinWorld.set(1, coin2Pointer.getX(), coin2Pointer.getY());
	coinWorld.set(2, coin3Pointer.getX(), coin3Pointer.getY());

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

void worldMap(robot& robotPointer, world& wPoint) {


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
			//pauses in between loop
			delay(111);
			clearScreen();
		}
	}
	cout << endl << "Robot found all coins. Searching finished." << endl;

}


void coinAndOtherDetails(world& w) {

	//prints necessary details on screen
	w.print();
	//cout << "W  O  R  L  D          M  A  P" << endl;
	cout << "    _      __  ____    ___    __     ___        __  ___  ___     ___ " << endl;
	cout << "   | | /| / / / __ \\  / _ \\  / /    / _ \\      /  |/  / / _ |   / _ \\"<< endl;
	cout << "   | |/ |/ / / /_/ / / , _/ / /__  / // /     / /|_/ / / __ |  / ___/" << endl;
	cout << "   |__/|__/  \\____/ /_/|_| /____/ /____/     /_/  /_/ /_/ |_| /_/   " << endl;
	cout << "                                                                   " << endl;

}

