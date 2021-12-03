#include "knight.hpp"

#include "board.hpp"

#include <iostream>

extern Board Bd;

std::vector<std::pair<int, int>> Knight::get_valid_moves()
{
	std::vector<std::pair<int, int>> moves;

	// these are the eight possible ways a Knight can move, the run and then rise, 
	// from its current position
	std::vector<std::pair<int, int>> possible_directions{
		{2,1},
		{1,2},
		{-1,2},
		{-2,1},
		{-2,-1},
		{-1,-2},
		{1,-2},
		{2,-1}
	};

	std::cout << "checking knight's moves" << std::endl;

	int r = get_position().first, c = get_position().second;
	for (int i = 0; i < possible_directions.size(); i++)
	{
		// the possibly valid move we are assessing
		int loop_r = r + possible_directions[i].first,
			loop_c = c + possible_directions[i].second;

		// if the move is to a space that doesn't exist on the board, coninue to the next possible move
		if (Board::off_board(loop_r,loop_c)) continue;

		std::cout << "(" << loop_r << "," << loop_c << ")" << std::endl;

		// else if this space exists on the board, check if it is a valid move
		check_valid(&moves, loop_r, loop_c);
	}

	return moves;
}