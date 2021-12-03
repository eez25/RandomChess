#pragma once

#include <utility>

class Move
{
public:
	char moved_name;
	std::pair<int, int> from;
	std::pair<int, int> to;
	char captured_name;
	Move(char moved_name, std::pair<int, int> from, std::pair<int, int> to, char captured_name);
};