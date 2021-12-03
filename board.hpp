#pragma once

#include <vector>
#include <string>

#include "piece.hpp"

const int BOARD_LENGTH = 8;
const std::vector<Piece> all_pieces;

enum class Col {
	A = 0,
	B = 1,
	C = 2,
	D = 3,
	E = 4,
	F = 5,
	G = 6,
	H = 7
};

class Board
{
public:
	// constructor
	Board();

	// deletes the piece memory that exists in the heap
	void delete_heap_mem();

	//holds the pieces active on the board in their appropriate spaces
	std::vector<std::vector<Piece*>> board;

	//holds pointers to all the pieces
	std::vector<Piece*> pieces;

	//retrieves the pieces in the given vector who meet the criteria passed in
	std::vector<Piece*> get_active_pieces(PType pt, Team t);
	std::vector<Piece*> get_active_pieces(PType pt);
	std::vector<Piece*> get_active_pieces(Team t);

	//determines if the team given has checkmated the other team
	bool has_checkmate(Team t);

	//determines if the team given has checked the other team
	std::vector<Piece*> get_checking_pieces(Team t);

	//removes a piece from the board and makes it inactive; returns false if the piece is already off the board
	bool remove_piece(Piece* p);

	//replaces a piece on the board and makes it active; returns false if the piece is already on the board
	bool replace_piece(Piece* p, std::pair<int, int> pos);

	// moves Piece p to board space pos and handles chain reactions such as removing pieces that were captured
	void move(Piece* p, std::pair<int, int> pos);

	// choses a random valid move and makes; assumes no checkmate
	Move random_move();

	// returns true if the space at (r,c) is not on the board
	static bool off_board(int r, int c);

	/* returns the spaces on the board that can be blocked in order to remove the king from being checked;
	 * this must be the intersection of each threatener's blockables because one piece must block all
	 * threateners or else the king will be captured in the next turn; already sorted */
	std::vector < std::pair<int, int>> get_necessary_blocks(std::vector<Piece*> threateners);
};