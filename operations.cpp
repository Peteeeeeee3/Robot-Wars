#include "operations.h"
#include "robot.h"
#include "map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//lists all robots in ascending order of robot ID
void show(vector<robot>& v) { //vector is passed through as reference, as sorting the original vector does not affect the rest of the program
	sort(v.begin(), v.end(), [](const robot& r1, const robot& r2) { return r1.getID() < r2.getID(); }); //sorta robots in ascending order according to their ID
	for (auto p : v)
		cout << p.getID() << " " << p.getTeam() << " " << p.getXCoordinate() << " " << p.getYCoordinate() << '\n'; //prints out data the same format of start.txt
}

//displays distance travelled by robots
void travelled(vector<robot>& v) { //vector is passed through as reference, as sorting the original vector does not affect the rest of the program
	sort(v.begin(), v.end(), [](const robot& r1, const robot& r2) {  //sorts robots according to requirements
		if (r1.getDistance() == r2.getDistance()) { //checks whether two robots have travelled same direction
			return r1.getID() < r2.getID(); //if distance is shared, robots are order according to the ID in ascending order
		} else
		{
			return r1.getDistance() < r2.getDistance(); //otherwise robots are ordered according to the distance travelled in ascending order
		}});
	for (auto &p : v)
		cout << p.getID() << " " << p.getDistance() << '\n'; //prints out appropriate data
}

//prints the robots within n distance of the origin (0, 0)
void within(const int& n, vector<robot> v) { //vector<robot> v is passed through as a copy, as to not affect the coordinates of the robots
	int num = 0; //tracks the number of robots within a distance of n
	for (auto &p : v) { //loops through all robots
		if (p.getXCoordinate() < 0) //if the x-coordinate is negative, set it to its absolute value
			p.setXCoordinate(abs(p.getXCoordinate()));
		if (p.getYCoordinate() < 0) //if the y-coordinate is negative, set it to its absolute value
			p.setYCoordinate(abs(p.getYCoordinate()));
		if (p.getXCoordinate() + p.getYCoordinate() <= n) //if the robot is within range, increment num
			++num;
	}
	cout << num << '\n';
}

//checks for matching ID
vector<robot>::iterator id_check(const int& id, vector<robot>& r) {
	auto temp = find_if(r.begin(), r.end(), [id](robot check) { return check.getID() == id; }); //returns the iterator of the robot with matching ID
	return temp;
}

//get the case value for the direction
int hash_direction(const string& dir) {
	if (dir == "north")
		return 1;
	else if (dir == "east")
		return 2;
	else if (dir == "south")
		return 3;
	else
		return 4;
}

//makes the robot turn left (e.g. if the robot faced north before, it will now face west)
void turnLeft(const int& id, vector<robot>& r) {
	auto temp = id_check(id, r); //temp is set to the iterator of the robot with the desired ID
	if (temp != r.end()) { //checks whether temp is within the vector's range
		switch (hash_direction(temp->getDirection())) //changes the direction the robot is facing according to the direction it is currently facing
		{
		case 1:
			temp->setDirection("west");
			break;
		case 2:
			temp->setDirection("north");
			break;
		case 3:
			temp->setDirection("east");
			break;
		case 4:
			temp->setDirection("south");
			break;
		}
	}
}

//makes the robot turn right (e.g. if the robot faced north before, it will now face east)
void turnRight(const int& id, vector<robot>& r) {
	auto temp = id_check(id, r); //temp is set to the iterator of the robot with the desired ID
	if (temp != r.end()) { //checks whether temp is within the vector's range
		switch (hash_direction(temp->getDirection())) //changes the direction the robot is facing according to the direction it is currently facing
		{
		case 1:
			temp->setDirection("east");
			break;
		case 2:
			temp->setDirection("south");
			break;
		case 3:
			temp->setDirection("west");
			break;
		case 4:
			temp->setDirection("north");
			break;
		}
	}
}

//makes the robot move forward one
void move(const int& id, vector<robot>& r) {
	auto to_move = id_check(id, r); // to_move is set to the iterator of the robot with the desired ID
	if (to_move != r.end()) { //checks whether temp is within the vector's range
		int x = to_move->getXCoordinate(); //stores the x coordinate of to_move
		int y = to_move->getYCoordinate(); //stores the y coordinate of to_move

		switch (hash_direction(to_move->getDirection())) //selects correct case according to direction to_move is facing
		{
			case 1:
			{
				//checks whether there is another robot in position the to_move is supposed to move to
				auto temp = find_if(r.begin(), r.end(), [x, y](robot robot) { return robot.getXCoordinate() == x && robot.getYCoordinate() == y + 1; });
				if (temp != r.end()) { //checks if a robot sharing the future position is found
					if (temp->getTeam() != to_move->getTeam()) { //checks wether this robot is on an enemy team
						temp->~robot(); //destroys opposing robot
						r.erase(temp); //removes destroyed robot from vector
						to_move->setYCoordinate(y + 1); //updates appropriate coordinate accordingly
						to_move->incrementDistance(); //increments the distance travelled by to_move
					}
				}
				else //if no robot has been found
				{
					to_move->setYCoordinate(y + 1); //updates appropriate coordinate accordingly
					to_move->incrementDistance(); //increments the distance travelled by to_move
				}
				break;
			}
			case 2: //same as case one, with only differences in coordiinate values
			{
				auto temp = find_if(r.begin(), r.end(), [x, y](robot robot) { return robot.getXCoordinate() == x + 1 && robot.getYCoordinate() == y; });
				if (temp != r.end()) {
					if (temp->getTeam() != to_move->getTeam()) {
						temp->~robot();
						r.erase(temp);
						to_move->setXCoordinate(x + 1);
						to_move->incrementDistance();
					}
				}
				else
				{
					to_move->setXCoordinate(x + 1);
					to_move->incrementDistance();
				}
				break;
			}
			case 3: //same as case one, with only differences in coordiinate values
			{
				auto temp = find_if(r.begin(), r.end(), [x, y](robot robot) { return robot.getXCoordinate() == x && robot.getYCoordinate() == y - 1; });
				if (temp != r.end()) {
					if (temp->getTeam() != to_move->getTeam()) {
						temp->~robot();
						r.erase(temp);
						to_move->setYCoordinate(y - 1);
						to_move->incrementDistance();
					}
				}
				else
				{
					to_move->setYCoordinate(y - 1);
					to_move->incrementDistance();
				}
				break;
			}
			case 4: //same as case one, with only differences in coordiinate values
			{
				auto temp = find_if(r.begin(), r.end(), [x, y](robot robot) { return robot.getXCoordinate() == x - 1 && robot.getYCoordinate() == y; });
				if (temp != r.end()) {
					if (temp->getTeam() != to_move->getTeam()) {
						temp->~robot();
						r.erase(temp);
						to_move->setXCoordinate(x - 1);
						to_move->incrementDistance();
					}
				}
				else
				{
					to_move->setXCoordinate(x - 1);
					to_move->incrementDistance();
				}
				break;
			}
		}
	}
}
