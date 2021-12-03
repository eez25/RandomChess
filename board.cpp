#include "board.hpp"

#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "piece.hpp"

#include <random>
#include <iterator>
#include <iostream>

extern Team COMP_TEAM;
extern Team USER_TEAM;

std::vector<Piece*> generate_back_row(Team t, int r)
{

	Rook* r1 = new Rook(t, r, (int)Col::A);
	Rook* r2 = new Rook(t, r, (int)Col::H);
	Knight* n1 = new Knight(t, r, (int)Col::B);
	Knight* n2 = new Knight(t, r, (int)Col::G);
	Bishop* b1 = new Bishop(t, r, (int)Col::C);
	Bishop* b2 = new Bishop(t, r, (int)Col::F);
	King* k = new King(t, r, (int)Col::E);
	Queen* q = new Queen(t, r, (int)Col::D);

	std::vector<Piece*> row{
		r1,
		n1,
		b1,
		q,
		k,
		b2,
		n2,
		r2
	};

	return row;
}

std::vector<Piece*> generate_pawn_row(Team t, int r)
{
	std::vector<Piece*> row;
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		Pawn* p = new Pawn(t, r, i);
		row.push_back(p);
	}
	return row;
}

std::vector<Piece*> generate_empty_row()
{
	std::vector<Piece*> row;
	for (int i = 0; i < BOARD_LENGTH; i++)
	{
		row.push_back(Piece::get_empty());
	}
	return row;
}

void Board::delete_heap_mem()
{
	for (Piece* p : pieces)
	{
		switch (p->get_type())
		{
		case PType::K:
			delete (King*)p;
			break;
		case PType::Q:
			delete (Queen*)p;
			break;
		case PType::B:
			delete (Bishop*)p;
			break;
		case PType::N:
			delete (Knight*)p;
			break;
		case PType::R:
			delete (Rook*)p;
			break;
		case PType::P:
			delete (Pawn*)p;
			break;
		case PType::E:
			delete p;
			break;
		}
	}
}

Board::Board()
{
	// generate the board's pieces in their rows
	std::vector<Piece*> white_back = generate_back_row(Team::White, 0),
		white_pawn = generate_pawn_row(Team::White, 1),
		black_pawn = generate_pawn_row(Team::Black, 6),
		black_back = generate_back_row(Team::Black, 7);

	// STL algorithm
	// add all the new pieces to the active_pieces vector
	pieces.insert(pieces.end(), white_back.begin(), white_back.end());
	pieces.insert(pieces.end(), white_pawn.begin(), white_pawn.end());
	pieces.insert(pieces.end(), black_pawn.begin(), black_pawn.end());
	pieces.insert(pieces.end(), black_back.begin(), black_back.end());

	// fill out the board with the new rows and with pointers to the Empty Piece for empty spaces
	board.push_back(white_back);
	board.push_back(white_pawn);
	for (int i = 2; i < BOARD_LENGTH - 2; i++)
	{
		board.push_back(generate_empty_row());
	}
	board.push_back(black_pawn);
	board.push_back(black_back);
}

bool same_type_team(Piece* p, PType pt, Team t)
{
	return *p == std::pair(pt, t);
}

bool same_type(Piece* p, PType pt, Team t)
{
	return p->get_type() == pt;
}

bool same_team(Piece* p, PType pt, Team t)
{
	return p->get_team() == t;
}

// uses function pointers to above boolean methods
// returns: the pieces in vec that have the attributes pt and/or t as decided by check_same
std::vector<Piece*> check_pieces(bool (*check_same)(Piece*, PType, Team), std::vector<Piece*> vec, PType pt, Team t)
{
	std::vector<Piece*> ret;
	for (Piece* p : vec)
	{
		if (p->get_active() && check_same(p, pt, t))
		{
			ret.push_back(p);
		}
	}
	return ret;
}

// passes function pointer as parameter
// returns: the active pieces of PType pt and Team t
std::vector<Piece*> Board::get_active_pieces(PType pt, Team t)
{
	return check_pieces(same_type_team, pieces, pt, t);
}

// passes function pointer as parameter
// returns: the active pieces of PType pt
std::vector<Piece*> Board::get_active_pieces(PType pt)
{
	return check_pieces(same_type, pieces, pt, Team::Empty);
}

// passes function pointer as parameter
// returns: the active pieces of Team t
std::vector<Piece*> Board::get_active_pieces(Team t)
{
	return check_pieces(same_team, pieces, PType::E, t);
}

bool Board::has_checkmate(Team t)
{
	// get opposing king
	Piece* king = get_active_pieces(PType::K, Piece::opposite(t))[0];

	// no checkmate if king can move
	if (king->get_valid_moves().size() > 0) return false;

	std::vector<Piece*> kings_team = get_active_pieces(Piece::opposite(t));

	// else if king cannot move, is he unblockably threatened?
	std::vector<std::pair<int, int>> need_to_block = get_necessary_blocks(get_checking_pieces(t));

	// if there are nochecks to block, there cannot be a checkmate
	if (need_to_block.size() == 0) return false;

	for (Piece* potential_blocker : kings_team)
	{
		std::vector < std::pair<int, int>> intersect,
			can_be_blocked = potential_blocker->get_valid_moves();

		// STL algorithm
		std::sort(can_be_blocked.begin(), can_be_blocked.end());

		std::set_intersection(
			need_to_block.begin(), need_to_block.end(),
			can_be_blocked.begin(), can_be_blocked.end(),
			std::back_inserter(intersect));

		// if threateners can be blocked, no checkmate
		if (intersect.size() > 0) return false;
	}

	// if no piece could block the threateners, checkmate
	return true;
}

std::vector<Piece*> Board::get_checking_pieces(Team t)
{
	// get team t's active pieces and the opposing king
	std::vector<Piece*> pieces = get_active_pieces(t),
		checking_pieces;
	Piece* king = get_active_pieces(PType::K, Piece::opposite(t))[0];

	// if any of these pieces are threatening the opposing king, return true
	for (Piece* p : pieces)
	{
		if (p->is_threatening(king->get_position())) checking_pieces.push_back(p);
	}
	return checking_pieces;
}

bool Board::remove_piece(Piece* p)
{
	// if p is already inactive, return false that we can't make it inactive
	if (not p->get_active()) return false;

	// otherwise, set p to inactive
	p->set_active(false);

	// set the piece at this board space to be empty
	board[p->get_position().first][p->get_position().second] = Piece::get_empty();

	return true;
}

bool Board::replace_piece(Piece* p, std::pair<int, int> pos)
{
	// if p is already active, return false that we can't make it inactive
	if (p->get_active()) return false;

	// otherwise, set it to active and update its position
	p->set_active(true);
	p->set_position(pos);

	// set this piece to its proper place on the board
	board[pos.first][pos.second] = p;

	return true;
}

void Board::move(Piece* p, std::pair<int, int> pos)
{
	Piece* old = board[pos.first][pos.second];

	// remove the old piece if there is one
	if (old != Piece::get_empty()) remove_piece(old);

	// move this piece to the new place
	board[pos.first][pos.second] = p;

	// put nothing in the place this piece used to occupy
	board[p->get_position().first][p->get_position().second] = Piece::get_empty();

	// update the position attribute to be the new location
	p->set_position(pos);
}

Move Board::random_move()
{
	// get the possible pieces the computer can move
	std::vector<Piece*> comp_pieces = get_active_pieces(COMP_TEAM);

	// get necessary moves and flag need_to_block if applicable
	std::vector<std::pair<int, int>> blocks = get_necessary_blocks(get_checking_pieces(USER_TEAM));
	bool need_to_block = blocks.size() > 0;

	// container for moves to randomly choose from
	std::vector < std::pair<
		std::pair<int, int>,
		std::pair<int, int>>> all_valid_moves;

	for (Piece* p : comp_pieces)
	{
		std::vector<std::pair<int, int>> valid_moves = p->get_valid_moves();

		// if there are spaces that need to be blocked, ignore possible moves that don't block them
		if (need_to_block)
		{
			// STL algorithm
			std::sort(valid_moves.begin(), valid_moves.end());

			std::vector<std::pair<int, int>> intersect;
			std::set_intersection(
				valid_moves.begin(), valid_moves.end(),
				blocks.begin(), blocks.end(),
				std::back_inserter(intersect)
			);
			valid_moves = intersect;
		}

		for (std::pair<int, int> move : valid_moves)
		{
			all_valid_moves.emplace_back(p->get_position(), move);
		}
	}
	// randomly choose a move to make
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> range(0, all_valid_moves.size());
	int i = range(rng);

	// collect data about the move
	std::pair<int, int> from = all_valid_moves[i].first,
		to = all_valid_moves[i].second;
	char moved_name = board[from.first][from.second]->get_name(),
		captured_name = board[to.first][to.second]->get_name();

	// make the move
	board[from.first][from.second]->move(to);
	return Move(moved_name, from, to, captured_name);
}

bool Board::off_board(int r, int c)
{
	return r < 0 || r >= BOARD_LENGTH || c < 0 || c >= BOARD_LENGTH;
}

std::vector<std::pair<int, int>> Board::get_necessary_blocks(std::vector<Piece*> threateners)
{
	std::vector<std::pair<int, int>> necessary_blocks;
	bool needs_init = true;

	// check how to block each threatener
	for (Piece* threatener : threateners)
	{
		// if this is the first threatener we're looking at
		if (needs_init)
		{
			necessary_blocks = threatener->get_blockables();
			std::sort(necessary_blocks.begin(), necessary_blocks.end());
			needs_init = false;
			continue;
		}

		// otherwise
		std::vector<std::pair<int, int>> intersect,
			blockables = threatener->get_blockables();

		// STL algorithm
		std::sort(blockables.begin(), blockables.end());

		// get the intersection of the ways to block threateners we have and are looking at
		std::set_intersection(
			necessary_blocks.begin(), necessary_blocks.end(),
			blockables.begin(), blockables.end(),
			std::back_inserter(intersect));

		// resets for next loop to be the cumulative intersection; can be size 0
		necessary_blocks = intersect;
	}

	// already sorted
	return necessary_blocks;
}