#include "bishop.hpp"

#include "board.hpp"

extern Board Bd;

std::vector<std::pair<int, int>> Bishop::get_valid_moves()
{
	std::vector<std::pair<int, int>> moves;

	int r = get_position().first, c = get_position().second;

	// a Bishop can move diagonally until it meets another piece, and can 
	// capture it if it's an enemy

	// check the positive, positive direction
	for (int i = 1; i < std::min(BOARD_LENGTH - r, BOARD_LENGTH - c); i++)
	{
		if (check_valid(&moves, r + i, c + i)) break;
	}

	// check the negative, negative direction
	for (int i = 1; i < std::min(r + 1, c + 1); i++)
	{
		if (check_valid(&moves, r - i, c - i)) break;
	}

	// check the positive, negative direction
	for (int i = 1; i < std::min(BOARD_LENGTH - r, c + 1); i++)
	{
		if (check_valid(&moves, r + i, c - i)) break;
	}

	// check the negative, positive direction
	for (int i = 1; i < std::min(r + 1, BOARD_LENGTH - c); i++)
	{
		if (check_valid(&moves, r - i, c + i)) break;
	}

	return moves;
}

std::vector<std::pair<int, int>> Bishop::get_blockables()
{
	std::vector<std::pair<int, int>> blockables;

	std::pair<int, int> bis_pos = get_position(),
		king_pos = Bd.get_active_pieces(PType::K, Piece::opposite(get_team()))[0]->get_position();

	int diff = bis_pos.first - king_pos.first;

	// to block the bishop from checking, one can capture it or block any space between it and the king
	for (int i = 0; i != diff; diff > 0 ? i++ : i--)
	{
		blockables.emplace_back(bis_pos.first + i, bis_pos.second + i);
	}

	return blockables;
}