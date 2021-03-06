#pragma once

#include "piece.hpp"

#include "board.hpp"

class Rook : public Piece
{
public:
	//constructor
	Rook(Team team, int r, int c) : Piece(PType::R, team, std::pair(r, c)) {}
	Rook() = default;

	// returns: a vector of the possible moves that can be made by this piece
	std::vector<std::pair<int, int>> get_valid_moves();

	/* precondition: this piece is checking the opposing king
       returns: a vector of the possible moves that can block this piece from checking the king */
	std::vector<std::pair<int, int>> get_blockables();
};