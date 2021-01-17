#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "robot.h"
#include "map.h"
#include <vector>
#include <string>

void show(std::vector<robot>& v); //function called for command "show"
void travelled(std::vector<robot>& v); //function called for command "travelled"
void within(const int& n, std::vector<robot> v); //function called for command "within"
void turnLeft(const int& id, std::vector<robot>& r); //function called for command "turnleft"
void turnRight(const int& id, std::vector<robot>& r); //function called for command "turnright"
void move(const int& id, std::vector<robot>& r); //function called for command "move"

#endif // !OPERATIONS_H