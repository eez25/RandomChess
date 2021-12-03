#include "queen.hpp"

#include "board.hpp"

#include <algorithm>
#include <iostream>

extern Board Bd;

std::vector<std::pair<int, int>> Queen::get_valid_moves()
{
	// The Queen has the sum of the movement rules of the Rook and the Bishop
	//std::vector<std::pair<int, int>> horiz_vert_moves = ((Rook*)this)->get_valid_moves(),
		//diagonal_moves = ((Bishop*)this)->get_valid_moves();

	std::cout << "getting Rook moves" << std::endl;
	std::vector<std::pair<int, int>> horiz_vert_moves = Rook::get_valid_moves();
	std::cout << "getting Bishop moves" << std::endl;
	std::vector<std::pair<int,int>> diagonal_moves = Bishop::get_valid_moves();
	std::cout << "gotten" << std::endl;

	// if one of these sets of moves is empty, don't bother concatenating them
	if (horiz_vert_moves.size() == 0) return diagonal_moves;
	if (diagonal_moves.size() == 0) return horiz_vert_moves;

	std::cout << "gluing them together" << std::endl;

	// STL algorithm
	horiz_vert_moves.insert(horiz_vert_moves.begin(),
		diagonal_moves.begin(),
		diagonal_moves.end());

	return horiz_vert_moves;
}