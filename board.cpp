#include "board.hpp"

#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "queen.hpp"
#include "rook.hpp"
#include "piece.hpp"

#include <random>
#include <iostream>

extern Team COMP_TEAM;

std::vector<Piece*> generate_back_row(Team t, int r)
{
	
	Rook* r1 = new Rook(t, r, (int)Col::A);
	Rook* r2 = new Rook(t, r, (int)Col::H);
	Knight* n1 = new Knight(t, r, (int)Col::B); 
	Knight* n2 = new Knight(t, r, (int)Col::G);
	Bishop* b1 = new Bishop(t, r, (int)Col::C);
	Bishop* b2 = new Bishop(t, r, (int)Col::F);
	King* k = new King(t, r, (int)Col::D);
	Queen* q = new Queen(t, r, (int)Col::E);

	std::vector<Piece*> row{
		r1,
		n1,
		b1,
		k,
		q,
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
	for (Piece* p : active_pieces)
	{
		delete p;
	}
	for (Piece* p : removed_pieces)
	{
		delete p;
	}
}

Board::Board()
{
	// generate the board's pieces in their rows
	std::vector<Piece*> white_back = generate_back_row(Team::White, 0),
		white_pawn = generate_pawn_row(Team::White, 1),
		black_pawn = generate_pawn_row(Team::Black, 6),
		black_back = generate_back_row(Team::Black, 7),
		active_pieces;

	// STL algorithm
	// add all the new pieces to the active_pieces vector
	active_pieces.insert(active_pieces.end(), white_back.begin(), white_back.end());
	active_pieces.insert(active_pieces.end(), white_pawn.begin(), white_pawn.end());
	active_pieces.insert(active_pieces.end(), black_pawn.begin(), black_pawn.end());
	active_pieces.insert(active_pieces.end(), black_back.begin(), black_back.end());

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

//uses function pointers to above boolean methods
std::vector<Piece*> check_pieces(bool (*check_same)(Piece*, PType, Team), std::vector<Piece*> vec, PType pt, Team t)
{
	std::vector<Piece*> ret;
	for (Piece* p : vec)
	{
		if (check_same(p, pt, t))
		{
			ret.push_back(p);
		}
	}
	return ret;
}

//passes function pointer as parameter
std::vector<Piece*> Board::get_pieces(std::vector<Piece*> vec, PType pt, Team t)
{
	return check_pieces(same_type_team, vec, pt, t);
}

//passes function pointer as parameter
std::vector<Piece*> Board::get_pieces(std::vector<Piece*> vec, PType pt)
{
	return check_pieces(same_type, vec, pt, Team::Empty);
}

//passes function pointer as parameter
std::vector<Piece*> Board::get_pieces(std::vector<Piece*> vec, Team t)
{
	return check_pieces(same_team, vec, PType::E, t);
}


bool Board::has_checkmate(Team t)
{
	// get opposing king
	Piece* king = get_pieces(active_pieces, PType::K, Piece::opposite(t))[0];

	// true if he has no moves and is_threatened AND TODO CANNOT BE PROTECTED
	return king->get_valid_moves().size() == 0 && has_check(t);
}

bool Board::has_check(Team t)
{
	// get team t's active pieces and the opposing king
	std::vector<Piece*> pieces = get_pieces(active_pieces, t);
	Piece* king = get_pieces(active_pieces, PType::K, Piece::opposite(t))[0];


	// if any of these pieces are threatening the opposing king, return true
	for (Piece* p : pieces)
	{
		if (p->is_threatening(king->get_position())) return true;
	}
	return false;
}

//removes an element from remove_from and adds it to add_to; returns false if it is not in remove_from
bool switch_vecs(std::vector<Piece*> add_to, std::vector<Piece*> remove_from, Piece* element)
{
	//STL algorithm
	std::vector<Piece*>::iterator found_el = std::find(remove_from.begin(), remove_from.end(), element);

	//return false if the piece is already not there (so find returned the last element instead)
	if (found_el[0] != element) return true;

	//if the piece is in the vector we want to remove it from
	remove_from.erase(found_el);
	add_to.push_back(element);
	return false;
}

bool Board::remove_piece(Piece* p)
{
	// attempt to move p from removed to active and return false if not possible
	bool already_gone = switch_vecs(removed_pieces, active_pieces, p);
	if (already_gone) return false;

	// set the piece at this board space to be empty
	board[p->get_position().first][p->get_position().second] = Piece::get_empty();

	return true;
}

bool Board::replace_piece(Piece* p, std::pair<int, int> pos)
{
	// attempt to move p from removed to active and return false if not possible
	bool already_gone = switch_vecs(active_pieces, removed_pieces, p);
	if (already_gone) return false;

	// set this piece to its proper place on the board
	board[p->get_position().first][p->get_position().second] = p;

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
	std::vector<Piece*> comp_pieces = get_pieces(active_pieces, COMP_TEAM);

	// calculate how many possible moves there are and use move counts as a distribution for picking a piece
	std::vector<int> num_moves(comp_pieces.size());
	int sum = 0, count;

	std::cout << "counts of possible moves:" << std::endl;

	for (Piece* p : comp_pieces)
	{
		count = (int)p->get_valid_moves().size();
		std::cout << p->get_name() << " at (" << p->get_position().first << ","
			<< p->get_position().second << ") has " << count << " moves." << std::endl;
		num_moves.push_back(count);
		sum += count;
	}

	// randomly generate a number in the count distribution
	std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> range(0, sum);
	int rand_int = range(rng);

	std::cout << sum << " " << rand_int << " corresponds to ";

	// determine which piece corresponds to that number in the distribution
	for (int i = 0; i < comp_pieces.size(); i++)
		{
		if (rand_int > num_moves[i])
		{
			rand_int -= num_moves[i];
			}
		else
		{
			std::cout << comp_pieces[i]->get_name() << std::endl;
			// if this is the piece the random number corresponds to, move it randomly
			Move m = comp_pieces[i]->random_move();
			return m;
		}
		}
}