#pragma once
#include <map>

class Command {
private:
	std::map<std::string, int (Command::*)()> mCommands;
public:
	Command();
};
