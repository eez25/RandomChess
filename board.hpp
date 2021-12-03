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

	// postcondition: the heap memory taken up by the board's pieces is released
	void delete_heap_mem();

	// holds the pieces active on the board in their appropriate spaces
	std::vector<std::vector<Piece*>> board;

	// holds pointers to all the pieces
	std::vector<Piece*> pieces;

	// returns: the active pieces of PType pt and/or Team t
	std::vector<Piece*> get_active_pieces(PType pt, Team t);
	std::vector<Piece*> get_active_pieces(PType pt);
	std::vector<Piece*> get_active_pieces(Team t);

	// returns: true if team t has checkmated the other team
	bool has_checkmate(Team t);

	// returns: the pieces on team t checking the opposing king
	std::vector<Piece*> get_checking_pieces(Team t);

	/* postcondition: piece p is removed from the board and set to inactive
	   returns: false if the piece is already off the board */
	bool remove_piece(Piece* p);

	/* postcondition: piece p is replaced onto the board and set to active
	   returns: false if the piece is already on the board */
	bool replace_piece(Piece* p, std::pair<int, int> pos);

	/* precondition: piece p can validly move to pos, as per get_valid_moves()
	   postcondition: piece p is at space pos and chain reactions such as removing captured pieces are handled */
	void move(Piece* p, std::pair<int, int> pos);

	/* precondition: the board is not in a state of checkmate
	   postcondition: the COMP_TEAM has moved one piece randomly to a valid position and chain 
	                  reactions are handled */
	Move random_move();

	// returns: true if the space at (r,c) is not on the board
	static bool off_board(int r, int c);

	/* returns: the sorted spaces on the board that can be blocked in order to stop the king from being checked
	   note: this must logically be the intersection of every threatener's blockables because one piece must
	         block all threateners at once or else the king will be captured in the next turn */
	std::vector < std::pair<int, int>> get_necessary_blocks(std::vector<Piece*> threateners);
};