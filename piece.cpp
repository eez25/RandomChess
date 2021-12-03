#include "piece.hpp"

#include <algorithm>
#include <random>
#include <iostream>

#include "board.hpp"
#include "printer.hpp"

extern Board Bd;
extern Team USER_TEAM;

Team Piece::opposite(Team t)
{
	switch (t)
	{
	case Team::Empty:
		return Team::Empty;
	case Team::White:
		return Team::Black;
	case Team::Black:
		return Team::White;
	}
}

Piece e = Piece();
Piece* empty = &e;
Piece* Piece::get_empty()
{
	return empty;
}

int Piece::forward()
{
	switch (team) {
	case Team::Empty:
		return 0;
	case Team::White:
		return 1;
	case Team::Black:
		return -1;
	}
}

Piece::Piece() : type(PType::E), team(Team::Empty), position(std::pair(-1, -1)), name(' '), active(false) {}

Piece::Piece(PType type, Team team, std::pair<int, int> position, bool active) :
	type(type),
	team(team),
	position(position),
	active(active)
{
	switch (type) {
	case PType::E:
		name = ' ';
		break;
	case PType::P:
		name = team == USER_TEAM ? 'P' : 'p';
		break;
	case PType::R:
		name = team == USER_TEAM ? 'R' : 'r';
		break;
	case PType::N:
		name = team == USER_TEAM ? 'N' : 'n';
		break;
	case PType::B:
		name = team == USER_TEAM ? 'B' : 'b';
		break;
	case PType::K:
		name = team == USER_TEAM ? 'K' : 'k';
		break;
	case PType::Q:
		name = team == USER_TEAM ? 'Q' : 'q';
		break;
	}
}

char Piece::get_name()
{
	return name;
}

Team Piece::get_team()
{
	return team;
}

PType Piece::get_type()
{
	return type;
}

std::pair<int, int> Piece::get_position()
{
	return position;
}

void Piece::set_position(std::pair<int, int> p)
{
	position = p;
}

bool Piece::get_active()
{
	return active;
}

void Piece::set_active(bool a)
{
	active = a;
}

// Overloaded operator
int Piece::operator == (Piece p)
{
	return (p.get_team() == team && p.get_type() == type);
}

int Piece::operator == (std::pair<PType, Team> t)
{
	return (type == t.first && team == t.second);
}

std::vector<std::pair<int, int>> Piece::get_valid_moves()
{
	std::cout << "THIS METHOD SHOULD NEVER BE CALLED: Piece::get_valid_moves()";
	std::vector<std::pair<int, int>> moves;
	return moves;
}

bool Piece::move(std::pair<int, int> coords)
{
	std::vector<std::pair<int, int>> valid_moves = get_valid_moves();

	std::cout << "checking for a move if it is not restricted by necessity" << std::endl;

	// check if there are any necessary blocks to be made to stop checking pieces from the opposite team
	std::vector<std::pair<int, int>> must_move_to = Bd.get_necessary_blocks(Bd.get_checking_pieces(Piece::opposite(get_team())));
	if (must_move_to.size() > 0)
	{
		// STL algorithm
		std::sort(valid_moves.begin(), valid_moves.end());

		std::vector<std::pair<int, int>> intersect;
		std::set_intersection(
			valid_moves.begin(), valid_moves.end(),
			must_move_to.begin(), must_move_to.end(),
			std::back_inserter(intersect));
		valid_moves = intersect;
	}

	// STL algorithm
	// return false if the move is invalid
	if (std::count(valid_moves.begin(), valid_moves.end(), coords) == 0) return false;

	// if the move is valid:
	Bd.move(this, coords);

	return true;
}

Move Piece::random_move()
{
	std::vector<std::pair<int, int>> m,
		possible_moves = get_valid_moves();

	// STL algorithm
	// pick a random move from the list of possible ones
	std::sample(possible_moves.begin(), possible_moves.end(), std::back_inserter(m), 1, std::mt19937{ std::random_device{}() });

	// collect move data
	std::pair<int, int> to = m[0];
	std::pair<int, int> from = get_position();
	char moved_name = get_name();
	char captured_name = Bd.board[to.first][to.second]->get_name();

	// do the thing
	move(to);

	// return what we did
	return Move(moved_name, from, to, captured_name);
}

bool Piece::is_threatening(std::pair<int, int> pos)
{
	std::vector<std::pair<int, int>> valid_moves = get_valid_moves();

	// true if this piece can move to this position on the board
	return std::count(valid_moves.begin(), valid_moves.end(), pos) > 0;
}

bool Piece::check_valid(std::vector<std::pair<int, int>>* moves, int r, int c)
{
	// if there is no piece there
	if (Bd.board[r][c] == Piece::get_empty())
	{
		moves->emplace_back(r, c);
		return false;
	}
	else {
		// if there is already piece here, this piece can move here if they are enemies
		if (Bd.board[r][c]->get_team() == opposite(get_team()))
			moves->emplace_back(r, c);
		return true;
	}
}

std::vector<std::pair<int, int>> Piece::get_blockables()
{
	std::vector<std::pair<int, int>> blockables;
	blockables.emplace_back(get_position());
	return blockables;
}

std::vector<std::pair<int, int>> Piece::get_valid_rook_moves()
{
	std::vector<std::pair<int, int>> moves;

	// a Rook can move up the board until it meets a piece, and can capture it if it is an enemy
	int c = get_position().second;
	for (int r = get_position().first + 1; r < BOARD_LENGTH; r++)
	{
		if (check_valid(&moves, r, c)) break;
	}

	// the same, down the board
	for (int r = get_position().first - 1; r >= 0; r--)
	{
		if (check_valid(&moves, r, c)) break;
	}

	// the same, to the right
	int r = get_position().first;
	for (int c = get_position().second + 1; c < BOARD_LENGTH; c++)
	{
		if (check_valid(&moves, r, c)) break;
	}

	// the same, down the board
	for (int c = get_position().second - 1; c >= 0; c--)
	{
		if (check_valid(&moves, r, c)) break;
	}

	return moves;
}

std::vector < std::pair<int, int>> Piece::get_rook_blockables()
{
	std::vector<std::pair<int, int>> blockables;

	std::pair<int, int> rook_pos = get_position(),
		king_pos = Bd.get_active_pieces(PType::K, Piece::opposite(get_team()))[0]->get_position();

	// if the rook and king are in the same row, the rook can be captured or any space between
	// them can be occupied to block the check
	if (rook_pos.first - king_pos.first == 0)
	{
		int r = rook_pos.first;
		for (int c = rook_pos.second; c != king_pos.second; king_pos.second > rook_pos.second ? c++ : c--)
		{
			blockables.emplace_back(r, c);
		}
	}

	// else if the rook and king are in the same column, same as above
	else {
		int c = rook_pos.second;
		for (int r = rook_pos.first; r != king_pos.first; king_pos.first > rook_pos.first ? r++ : r--)
		{
			blockables.emplace_back(r, c);
		}
	}

	return blockables;
}

std::vector<std::pair<int, int>> Piece::get_valid_bishop_moves()
{
	std::vector<std::pair<int, int>> moves;

	int r = get_position().first, c = get_position().second;

	// a Bishop can move diagonally until it meets another piece, and can 
	// capture it if it's an enemy

	// check the positive, positive direction
	for (int i = 1; i < std::min(BOARD_LENGTH - r, BOARD_LENGTH - c); i++)
	{
		if (check_valid(&moves, r + i, c + i)) break;
	}

	// check the negative, negative direction
	for (int i = 1; i < std::min(r + 1, c + 1); i++)
	{
		if (check_valid(&moves, r - i, c - i)) break;
	}

	// check the positive, negative direction
	for (int i = 1; i < std::min(BOARD_LENGTH - r, c + 1); i++)
	{
		if (check_valid(&moves, r + i, c - i)) break;
	}

	// check the negative, positive direction
	for (int i = 1; i < std::min(r + 1, BOARD_LENGTH - c); i++)
	{
		if (check_valid(&moves, r - i, c + i)) break;
	}

	return moves;
}

std::vector<std::pair<int, int>> Piece::get_bishop_blockables()
{
	std::vector<std::pair<int, int>> blockables;

	std::pair<int, int> bis_pos = get_position(),
		king_pos = Bd.get_active_pieces(PType::K, Piece::opposite(get_team()))[0]->get_position();

	int diff = std::abs(bis_pos.first - king_pos.first);

	// to block the bishop from checking, one can capture it or block any space between it and the king
	for (int i = 0; i < diff; i++)
	{
		// make sure we're moving in the direction from the bishop to the king
		int r = bis_pos.first > king_pos.first ? bis_pos.first - i : bis_pos.first + i,
			c = bis_pos.second > king_pos.second ? bis_pos.second - i : bis_pos.second + i;

		blockables.emplace_back(r,c);
	}

	return blockables;
}