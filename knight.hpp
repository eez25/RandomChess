#pragma once

#include "piece.hpp"

class Knight : public Piece
{
public:
	//constructor
	Knight(Team team, int r, int c) : Piece(PType::N, team, std::pair(r, c)) {}

	std::vector<std::pair<int, int>> get_valid_moves();
};