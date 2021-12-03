#include "move.hpp"

Move::Move(char moved_name, std::pair<int, int> from, std::pair<int, int> to, char captured_name = ' ') :
	moved_name(moved_name), from(from), to(to), captured_name(captured_name) {}