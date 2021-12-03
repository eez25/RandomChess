#include "bishop.hpp"

#include "board.hpp"
#include <iostream>

extern Board Bd;

std::vector<std::pair<int, int>> Bishop::get_valid_moves()
{
	return get_valid_bishop_moves();
}

std::vector<std::pair<int, int>> Bishop::get_blockables()
{
	return get_bishop_blockables();
}