#include "knight.hpp"

#include "board.hpp"

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

	int r = get_position().first, c = get_position().second;
	for (int i = 0; i < possible_directions.size(); i++)
	{
		// the possibly valid move we are assessing
		int loop_r = r + possible_directions[i].first,
			loop_c = c + possible_directions[i].second;

		// if the move is to a space that doesn't exist on the board, coninue to the next possible move
		if (r < 0 || r >= BOARD_LENGTH || c < 0 || c >= BOARD_LENGTH) continue;

		// else if this space exists on the board, check if it is a valid move
		Piece* p = Bd.board[loop_r][loop_c];
		check_valid(&moves, loop_r, loop_c);
	}

	return moves;
}