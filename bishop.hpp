#pragma once

#include "piece.hpp"

class Bishop : public Piece
{
public:
	//constructors
	Bishop(Team team, int r, int c) : Piece(PType::B, team, std::pair(r, c)) {}
	Bishop() = default;

	// returns: a vector of the possible moves that can be made by this piece
	std::vector<std::pair<int, int>> get_valid_moves();

	/* precondition: this piece is checking the opposing king
	   returns: a vector of the possible moves that can block this piece from checking the king */
	std::vector<std::pair<int, int>> get_blockables();
};