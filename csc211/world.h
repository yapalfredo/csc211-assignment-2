#pragma once
#include "point.h"

class world {
private:
	int coinLocation[3][1][2];
	const char worldMap[10][21] = {
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]",
		"[][][][][][][][][][]"
	};

public:
	world();
	~world();
	void print() const;
	void set(int, int, int);
	void printMap(int, int);
	int getCoordinate(int, int);

	bool coin1Found, coin2Found, coin3Found;

	


	
};

