#include "robot.h"
#include "operations.h"
#include "map.h"
#include "command.h"

#include <string>
#include <iostream>
#include <algorithm>


using namespace std;

int main()
{
    map battlefield; //creates an object battlefield of class map
    battlefield.readStart(); //reads data from start.txt and populates battlefield's vector with robots accordingly
    vector<command> commands = readCommands(); //creates a vector containing the commands read from commands.txt in correct order
    runCommands(commands, battlefield.getRobots()); //runs the commands stored in the vector

    return 0;
}