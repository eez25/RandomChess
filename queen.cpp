#include "queen.hpp"

#include "board.hpp"

#include <algorithm>

extern Board Bd;

std::vector<std::pair<int, int>> Queen::get_valid_moves()
{
	// The Queen has the sum of the movement rules of the Rook and the Bishop
	std::vector<std::pair<int, int>> horiz_vert_moves = get_valid_rook_moves(),
		diagonal_moves = get_valid_bishop_moves();

	// if one of these sets of moves is empty, don't bother concatenating them
	if (horiz_vert_moves.size() == 0) return diagonal_moves;
	if (diagonal_moves.size() == 0) return horiz_vert_moves;

	// STL algorithm
	horiz_vert_moves.insert(horiz_vert_moves.begin(),
		diagonal_moves.begin(),
		diagonal_moves.end());

	return horiz_vert_moves;
}

std::vector < std::pair<int, int>> Queen::get_blockables()
{
	std::pair<int, int> king_pos = Bd.get_active_pieces(PType::K, Piece::opposite(Piece::get_team()))[0]->get_position();

	// if the queen is threatening the king as a rook would, it can be blocked the same way as a rook
	if (get_position().first == king_pos.first || get_position().second == king_pos.second) return get_rook_blockables();

	// otherwise, it must be threatening the king as a bishop because of the precondition
	return get_bishop_blockables();
}