
#include <iostream>
#include "CommandHandler.h"

void handleCommand() {
	std::string command;
	std::cin >> command;
	std::string delimiter = " ";
	std::string initialCommand = command.substr(0, command.find(delimiter));

	//apply initial command to a lookup table, pass the command over to a dedicated handler function
}