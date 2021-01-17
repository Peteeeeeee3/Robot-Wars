#ifndef ROBOT_H
#define ROBOT_H

#include <string>

class robot {
	int robot_id, team, x, y, distance; //robot_id is assumed to be unique, a robot is part of either team one or two
	std::string direction; //Values for direction can be: "north", "east", "south" or "west"

public:

	robot(int id, int t, int X, int Y); //robot constructor
	~robot() {} //robot destructor
	const int& getID() const { return robot_id; } //returns ID
	const int& getTeam() const { return team; } //returns team
	const int& getXCoordinate() const { return x; } //returns x-coordinate
	const void setXCoordinate(const int& newX) { x = newX; } //updates x-coordinate value
	const int& getYCoordinate() const { return y; } //returns y-coordinate
	const void setYCoordinate(const int& newY) { y = newY; } //updates y-coordinate
	const std::string& getDirection() const { return direction; } //returns the direction the robot is facing
	const void setDirection(const std::string& d) { direction = d; } //updates the direction the robot is facing 
	const int& getDistance() const { return distance; } //returns the distance travelled by the robot
	const void incrementDistance() { distance += 1; } //increments the distance travlled by the robot, called when a robot takes a step forward in any direction
};

#endif // !ROBOT_H