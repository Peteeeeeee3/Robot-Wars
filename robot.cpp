#include "robot.h"

robot::robot(int id, int t, int X, int Y) : robot_id(id), team(t), x(X), y(Y) {
	direction = "north";
	distance = 0;
};