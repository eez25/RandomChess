#pragma once

#include "piece.hpp"

class Knight : public Piece
{
public:
	//constructor
	Knight(Team team, int r, int c) : Piece(PType::N, team, std::pair(r, c)) {}

	// returns: a vector of the possible moves that can be made by this piece
	std::vector<std::pair<int, int>> get_valid_moves();

	/* precondition: this piece is checking the opposing king
	   returns: a vector of the possible moves that can block this piece from checking the king */
	std::vector<std::pair<int, int>> get_blockables();
};