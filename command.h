#ifndef COMMAND_H
#define COMMAND_H

#include "robot.h"
#include <string>
#include <vector>

class command {
	std::string name; //records the name of the command, e.g. "within" from "within 7"
	int value; // records the integer value associated with the command, e.g. "7" from "within 7"

public:
	command(std::string s) : name(s) {} //constructor initializes only the name with the name of the command and leave the integer value to be NULL, 
	//as this is not important to the command
	command(std::string s, int n) : name(s), value(n) {} //constructor initializes both data members
	const std::string& getName() const { return name; } //returns name of command
	const int& getValue() const { return value; } //returns the value associated with the command
};

std::vector<command> readCommands(); //reads entered commands from commands.txt and stores them in a vector in the correct order
void runCommands(const std::vector<command>& c, std::vector<robot>& r); //runs commands from commands.txt in correct order

#endif // !COMMAND_H