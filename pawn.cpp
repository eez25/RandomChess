#include "pawn.hpp"

#include "board.hpp"
#include "printer.hpp"

#include <iostream>

extern Board Bd;

std::vector<std::pair<int, int>> Pawn::get_valid_moves()
{
	std::vector<std::pair<int, int>> moves;
	int f = forward();
	std::pair<int, int> pos = get_position();
	int r = pos.first, c = pos.second;

	// if there is space in front of the Pawn and it is not occupied, it can move there
	if (r + f >= 0 && r + f < BOARD_LENGTH
		&& Bd.board[r + f][c] == Piece::get_empty())
		moves.emplace_back(r + f, c);

	// if there is space diagonal to the right and an enemy there, the pawn can move there
	if (r + f >= 0 && r + f < BOARD_LENGTH 
		&& c - 1 > 0 
		&& Bd.board[r + f][c - 1]->get_team() == opposite(get_team()))
		moves.emplace_back(r - 1, c + f);

	// if there is space diagonal to the left and an enemy there, the pawn can move there
	if (r + f >= 0 && r + f < BOARD_LENGTH && c + 1 < BOARD_LENGTH && Bd.board[r + 1][c + f]->get_team() == opposite(get_team()))
		moves.emplace_back(r + 1, c + f);

	// if this Pawn is in the second row of its forward direction
	// and both spaces ahead are unoccupied, it can move up two
	if (f == 1 ? (r == 2 * f) : (r == BOARD_LENGTH + (2 * f) - 1)
		&& Bd.board[r + f][c] == Piece::get_empty()
		&& Bd.board[r + (2 * f)][c] == Piece::get_empty())
		moves.emplace_back(r, c + (2 * f));

	return moves;
}