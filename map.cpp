#include "map.h"
#include <fstream>
#include <iostream>

using namespace std;

//adds robot to the vector containing all robots
void map::addRobot(const robot& r) {
	robots.push_back(r);
}

//reads the start.txt file
void map::readStart() {
	ifstream file("start.txt");
	int no, team, x, y;

	while (file >> no >> team >> x >> y) {
		addRobot(robot(no, team, x, y));
	}
	file.close();
}