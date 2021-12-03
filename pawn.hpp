#pragma once

#include "piece.hpp"

class Pawn : public Piece
{
public:
	//constructor
	Pawn(Team team, int r, int c) : Piece(PType::P, team, std::pair(r, c)) {}

	std::vector<std::pair<int, int>> get_valid_moves();
};