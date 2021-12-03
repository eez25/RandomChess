#pragma once

#include <string>
#include <vector>

#include "move.hpp"

enum class PType
{
	P = 0, // Pawn
	R = 1, // Rook
	N = 2, // kNight
	B = 3, // Bishop
	Q = 4, // Queen
	K = 5, // King
	E = 6  // Empty
};

enum class Team
{
	White = 0,
	Black = 1,
	Empty = 2
};

class Piece
{
private:
	char name;
	Team team;
	PType type;
	std::pair<int, int> position;
	bool active;

public:
	// constructor
	Piece(PType type, Team team, std::pair<int, int> position, bool active = true);
	Piece();

	// returns a pointer to an empty Piece placeholder
	static Piece* get_empty();

	// returns 1 if the forward direction of this Piece's Team is positive or -1 if that is in the forward direction
	int forward();

	// getters
	char get_name();
	Team get_team();
	PType get_type();
	std::pair<int, int> get_position();
	bool get_active();

	// setters
	void set_position(std::pair<int, int> p);
	void set_active(bool a);

	// returns the opposite team
	static Team opposite(Team t);

	// Operator overloads
	int operator == (Piece p);
	int operator == (std::pair<PType, Team> t);

	// returns a vector of the possible moves that can be made given any pieces checking the king
	virtual std::vector<std::pair<int, int>> get_valid_moves();

	/* returns a vector of the possible moves that can block this piece from checking the king; 
	   assumes this piece is checking the opposing king; base Piece:: version assumes only way 
	   to block is to capture piece */ 
	virtual std::vector < std::pair<int, int>> get_blockables();

	/* moves a piece and handles chain reactions of other pieces needing to be removed, etc.
	   returns false if the move is invalid */
	bool move(std::pair<int, int> coords);

	// moves a piece to a valid location chosen uniformly at random
	Move random_move();

	// returns true if this piece is threatening the square at pos
	bool is_threatening(std::pair<int, int> pos);

	/* updates moves with the pair (r,c) if it is not occupied by a teammate piece;
	   returns true if there is already a piece there, enemy or not */
	bool check_valid(std::vector<std::pair<int, int>>* moves, int r, int c);
};