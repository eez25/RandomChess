#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
public:
	//constructor
	Pawn(Team team, int r, int c) : Piece(PType::P, team, std::pair(r, c)) {}

	// returns: a vector of the possible moves that can be made by this piece
	std::vector<std::pair<int, int>> get_valid_moves();

	/* precondition: this piece is checking the opposing king
	   returns: a vector of the possible moves that can block this piece from checking the king */
	std::vector<std::pair<int, int>> get_blockables();
};