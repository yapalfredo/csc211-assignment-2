#include "point.h"
#include "world.h"


class robot {
private:
	point posOfRobot;
	enum orientation_type { east, west, south, north } orientation;
	string name;
	void setFix_X(int); //helper function for undoing X last movement on the final loop
public:
	robot();
	robot(point);
	robot(string, point);
	~robot();

	int getX();
	int getY();

	void print(world&) const;
	void print(char) const;
	void turnCW(char);
	void turnAntiCW(char);
	void initTop();
	void initBottom();
	void setOrientation(orientation_type);
	
	bool eastEnd();
	bool westEnd();
	bool northEnd();
	bool southEnd();
	bool forward(); 
	bool reverse();
	bool zag(char); 
	bool zig(char);

	void fix_X(int); //undo's X last movement on the final loop
	
	float distance(robot&, robot&) const;
	robot operator-(robot&) const;
	bool operator==(robot&);
};