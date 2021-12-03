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

	std::vector<std::pair<int, int>> get_valid_moves();
};