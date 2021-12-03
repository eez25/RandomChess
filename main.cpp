#include "board.hpp"
#include "bishop.hpp"
#include "king.hpp"
#include "knight.hpp"
#include "pawn.hpp"
#include "printer.hpp"
#include "queen.hpp"
#include "rook.hpp"

#include <iostream>
#include <exception>

Board Bd;

Team COMP_TEAM = Team::Black;
Team USER_TEAM = Team::White;

// declarations for mutual recursion
void do_the_thing();

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

// announces end of game and prompts for and starts new game if wanted by player
void end_or_new_game(bool win)
{
	// tell the user the result of the game
	win ? printer::print_win() : printer::print_lose();

	// check if the player wants to play again
	std::string play;
	std::cin >> play;

	// restart the game to play again
	if (play == "again")
	{
		Bd.delete_heap_mem();
		Bd = Board();
		do_the_thing();
	}
	return;
}

/* postcondition: check and checkmate are handled
   returns: true if the user wants to quit after checkmate */
bool check_and_handle_game_conditions()
{
	// tell the user if there is a check
	if (Bd.get_checking_pieces(COMP_TEAM).size() > 0) std::cout << "The computer has put you in check!" << std::endl << std::endl;
	if (Bd.get_checking_pieces(USER_TEAM).size() > 0) std::cout << "You have put the computer in check!" << std::endl << std::endl;

	// check if the game is won
	if (Bd.has_checkmate(USER_TEAM))
	{
		printer::print_board(Bd);
		end_or_new_game(true);
		return true;
	}
	if (Bd.has_checkmate(COMP_TEAM))
	{
		printer::print_board(Bd);
		end_or_new_game(false);
		return true;
	}
	return false;
}

void do_the_thing()
{
	// return if the game is won (and if the user doesn't want to play again, which is checked in the function)
	if (check_and_handle_game_conditions()) return;

	// prompt user
	std::cout << std::endl;
	printer::print_prompt();

	// collect input, with 81 extra characters in case of input overflow, which was causing stack overflow
	char long_input[100], input[9];
	std::cin.getline(long_input, 100);
	std::strncpy(input, long_input, 9);

	std::cout << std::endl;

	// quit if that's the input
	if (std::strcmp(input, "quit") == 0) return;

	// otherwise, try to parse the input and do the thing
	try
	{
		// parse board spaces
		std::pair<int, int> from = { parse_row(input[1]),parse_col(input[0]) },
			to = { parse_row(input[7]),parse_col(input[6]) };

		// Checking that a user is allowed to move this piece
		if (Bd.board[from.first][from.second]->get_team() != USER_TEAM)
		{
			std::cout << "You are attempting to move a piece that is not yours.  ";
			throw std::exception();
		}

		// Attempt to move and if it is valid
		if (Bd.board[from.first][from.second]->move(to)) {

			// check for kings in check or checkmate
			// end the game if check_and_handle returns true that the user wants to quit after checkmate
			if (check_and_handle_game_conditions()) return;

			// if not, move the computer randomly
			Move m = Bd.random_move();

			// begin again to prompt the user for the next move
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
	// create a new board
	Bd = Board();

	// print intro
	std::cout << std::endl;
	printer::print_intro();
	printer::print_help();

	// prompt the user to move on from intro
	std::cout << "Hit the Enter key to begin!" << std::endl;
	std::cin.ignore();

	printer::print_board(Bd);

	// begin the prompt, collect input, perform action, repeat... cycle
	do_the_thing();

	return 0;
}