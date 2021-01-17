#include "command.h"
#include "operations.h"
#include <vector>
#include <fstream>

using namespace std;

//reads entered commands from commands.txt and stores them in a vector in the correct order
vector<command> readCommands() {
	ifstream file("commands.txt");
	string text;
	vector<string> words;
	vector<command> cmds;

	while (getline(file, text)) { //loops until no lines r left within the input file
		auto tmp = find_if(text.cbegin(), text.cend(), [](char s) {return s == ' '; }); //finds the location of a space (" ") within the command
		if (tmp != text.cend()) { //if there is a space, then it should create an object of class command an initialize both the integer and the string values
			cmds.push_back(command(string(text.cbegin(), tmp), stoi(string(tmp, text.cend()))));
		}
		else { //otherwise it should create an object of class command, but only initialize the string value
			cmds.push_back(command(text));
		}
	}
	file.close();
	return cmds;
}

//runs commands from commands.txt in correct order
void runCommands(const vector<command>& c, vector<robot>& r) {
	for (auto &p : c) { //loops through all commands within the vector
		//calls function appropriate to the command read
		if (p.getName() == "show")
			show(r);
		else if (p.getName() == "travelled")
			travelled(r);
		else if (p.getName() == "within")
			within(p.getValue(), r);
		else if (p.getName() == "turnleft")
			turnLeft(p.getValue(), r);
		else if (p.getName() == "turnright")
			turnRight(p.getValue(), r);
		else if (p.getName() == "move")
			move(p.getValue(), r);
	}
}
