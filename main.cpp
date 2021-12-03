#include "board.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "printer.hpp"
#include "queen.hpp"
#include "rook.hpp"

#include <iostream>

Board Bd;

Team COMP_TEAM = Team::Black;
Team USER_TEAM = Team::White;

int parse_col(char c)
{
	switch (c)
	{
	case 'A':
	case 'a':
		return 0;
	case 'B':
	case 'b':
		return 1;
	case 'C':
	case 'c':
		return 2;
	case 'D':
	case 'd':
		return 3;
	case 'E':
	case 'e':
		return 4;
	case 'F':
	case 'f':
		return 5;
	case 'G':
	case 'g':
		return 6;
	case 'H':
	case 'h':
		return 7;
	
	// if the character is none of the above, it is not accepted
	default:
		throw std::exception();
	}
}

int parse_row(char c)
{
	std::string valid_inputs = "12345678";

	// if the character is not a valid input, trigger the catch to tell the user so
	if (std::count(valid_inputs.begin(), valid_inputs.end(), c) == 0) throw std::exception();

	// else if it is valid, parse it to an int
	return int(c - '0') - 1;
}

void do_the_thing()
{
	// prompt user
	std::cout << std::endl;
	printer::print_prompt();

	// collect input
	char input[9];
	std::cin.getline(input,9);
	std::cout << std::endl;

	// quit if that's the input
	if (std::strcmp(input, "quit") == 0) return;

	// otherwise, try to parse the input and do the thing
	try
	{
		// parse board spaces
		std::pair<int, int> from = { parse_row(input[1]),parse_col(input[0]) },
			to = { parse_row(input[7]),parse_col(input[6]) };

		std::cout << "parsed input " << input << " -> " << from.first << "," << from.second << " to " 
			<< to.first << "," << to.second << std::endl;

		// Checking that a user is allowed to move this piece
		if (Bd.board[from.first][from.second]->get_team() != USER_TEAM)
		{
			std::cout << "You are attempting to move a piece that is not yours.  ";
			throw std::exception();
		}

		// Attempt to move and handle if it is valid or not
		if (Bd.board[from.first][from.second]->move(to)) { //valid
			Move m = Bd.random_move();
			printer::print_board(Bd);
			printer::print_comp_move(m);
			do_the_thing();
		}
		else { //invalid move; trigger catch block which handles incorrect inputs
			throw std::exception();
		}
	}

	// catches when the input is not correctly formed or when a correctly formed input is not a valid move
	catch (...)
	{
		printer::print_cant_do();
		printer::print_help();
		do_the_thing();
	}
}

int main()
{
	Bd = Board();

	std::cout << std::endl;
	printer::print_intro();
	printer::print_help();

	std::cout << "Hit the Enter key to begin!" << std::endl;
	std::cin.ignore();

	printer::print_board(Bd);

	do_the_thing();

	return 0;
}