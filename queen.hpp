#pragma once

#include "rook.hpp"
#include "bishop.hpp"
#include "board.hpp"

// Multiclass inheritance
class Queen : public Rook, public Bishop
{
public:
	//constructor
	Queen(Team team, int r, int c) : Piece(PType::Q, team, std::pair(r, c)) {}

	// returns: a vector of the possible moves that can be made by this piece
	std::vector<std::pair<int, int>> get_valid_moves();

	/* precondition: this piece is checking the opposing king
	   returns: a vector of the possible moves that can block this piece from checking the king */
	std::vector<std::pair<int, int>> get_blockables();
};