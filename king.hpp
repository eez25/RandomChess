#pragma once

#include "piece.hpp"

class King : public Piece
{
public:
	//constructor
	King(Team team, int r, int c) : Piece(PType::K, team, std::pair(r, c)) {}

	std::vector<std::pair<int, int>> get_valid_moves();
};