#pragma once

#include "piece.hpp"

class King : public Piece
{
public:
	//constructor
	King(Team team, int r, int c) : Piece(PType::K, team, std::pair(r, c)) {}

	// returns: a vector of the possible moves that can be made by this piece
	std::vector<std::pair<int, int>> get_valid_moves();

	/* returns: an empty vector because a king can never threaten another king, so it also cannot 
	   be blocked from doing so */
	std::vector<std::pair<int, int>> get_blockables();
};