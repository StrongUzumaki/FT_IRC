#pragma once

#include <string>
#include <vector>

#include "Message.hpp"

class Parser {
private:
	enum { PREFIX, COMMAND, PARAMETER } mTokenType;

	std::vector<std::string>& split(std::vector<std::string>& dst,
									const std::string& src,
									const std::string& delim);
public:
	Message	parse(const std::string& input);
};
