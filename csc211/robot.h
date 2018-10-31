#include "point.h"
#include "world.h"


class robot {
private:
	point posOfRobot;
	enum orientation_type { east, west, south, north } orientation;
	string name;
public:
	robot();
	robot(point);
	robot(string, point);
	~robot();

	int getX();
	int getY();

	void print(world&) const;
	void print() const;
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
};