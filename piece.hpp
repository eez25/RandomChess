#pragma once

#include <string>
#include <vector>

#include "move.hpp"

// enumerates the piece types that a piece can have: King, Queen, etc.
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

// enumerates the different sides in the game, Black and White
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
	// constructors
	Piece(PType type, Team team, std::pair<int, int> position, bool active = true);
	Piece();

	// returns: a pointer to an empty Piece placeholder
	static Piece* get_empty();

	/* returns: 1 if the piece's forward direction is up the board towards row 8 or -1 if the
	            forward direction is down the board toward row 1 */
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

	// returns: the opposite team
	static Team opposite(Team t);

	// Operator overloads
	int operator == (Piece p);
	int operator == (std::pair<PType, Team> t);

	// returns: a vector of the possible moves that can be made by this piece
	virtual std::vector<std::pair<int, int>> get_valid_moves();

	/* precondition: this piece is checking the opposing king
	   returns: a vector of the possible moves that can block this piece from checking the king
	   notes: for base Piece:: version, this return value only includes the space this piece occupies
			  as the only way to block it would be to capture it */
	virtual std::vector < std::pair<int, int>> get_blockables();

	/* postcondition: chain reactions such as removing a captured piece are handled
	   returns: false if the move is not valid */
	bool move(std::pair<int, int> coords);

	/* postcondition: moves a COMP_TEAM piece to a valid location chosen uniformly at random
	   returns: data about the move randomly taken in Move format */
	Move random_move();

	// returns: true if this piece is threatening the board square at pos
	bool is_threatening(std::pair<int, int> pos);

	/* precondition: moving to (r,c) is valid, as per get_valid_moves()
	   postcondition: moves includes (r,c) if it is not occupied by a teammate
	   returns: true if there is already a piece at this space */
	bool check_valid(std::vector<std::pair<int, int>>* moves, int r, int c);
};