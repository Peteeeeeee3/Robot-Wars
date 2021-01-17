#ifndef MAP
#define MAP

#include "robot.h"
#include <vector>

class map {
	std::vector<robot> robots; //this vector contains all of the robots read from start.txt

public:
	map() {} //constructor does not initialize the vector robots with any values
	void addRobot(const robot &r); //adds a robot to the vector
	std::vector<robot> &getRobots() { return robots; } //returns the vector robots containing all robots
	void readStart(); //reads the data from start.txt, creates robots according to these values and adds these robots to the vector robots
};

#endif // !MAP