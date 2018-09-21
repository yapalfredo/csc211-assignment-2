#include "robot.h"
#include "otherClasses.h"




int main(const int argc, char *argv[]) {

	//hide cursor
	ShowConsoleCursor(false);

	//clear console
	system("CLS"); system("CLS");

	//function call
	mainValidation(argc, argv);

	system("Pause");
	return 0;
}