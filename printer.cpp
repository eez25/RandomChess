#include <iostream>

#include "board.hpp"

#include "printer.hpp"

void printer::print_board(Board b)
{
	print_col_names();
	print_horiz();
	for (int i = 7; i >= 0; i--)
	{
		std::cout << " " << i + 1; print_row(b.board[i]); std::cout << " " << i + 1 << std::endl;
		print_horiz();
	}
	print_col_names();
}

// prints a horizontal line 
void printer::print_horiz()
{
	std::cout << "   +---+---+---+---+---+---+---+---+" << std::endl;
}

void printer::print_col_names()
{
	std::cout << "     A   B   C   D   E   F   G   H  " << std::endl;
}

// prints a single row of the board, including the pieces currently present on it
void printer::print_row(std::vector<Piece*> row)
{
	for (Piece* p : row)
	{
		std::cout << " | " << p->get_name();
		//p->get_name();
	}
	std::cout << " |";
}

void printer::print_prompt()
{
	std::cout << "What would you like to do?" << std::endl;
}

void printer::print_cant_do()
{
	std::cout << "That move is invalid." << std::endl;
}

void printer::print_help()
{
	std::cout
		<< "The uppercase pieces are yours.  Piece names are as follows:" << std::endl
		<< "    P - Pawn" << std::endl
		<< "    R - Rook" << std::endl
		<< "    N - kNight" << std::endl
		<< "    B - Bishop" << std::endl
		<< "    K - King" << std::endl
		<< "    Q - Queen" << std::endl
		<< std::endl
		<< "To move, type 'CR to CR' for char columns C and int rows R.  For example, to move a piece from " << std::endl
		<< "row 2 and column D to row 3 and column E, type 'D2 to E3'.  Lowercase column names are also" << std::endl
		<< "supported.  Type 'quit' to end the game." << std::endl
		<< std::endl;
}

void printer::print_comp_move(Move m)
{
	std::cout
		<< std::endl
		<< "Computer moves piece " << m.moved_name << " from " << char(m.from.second + 65) << m.from.first + 1
		<< " to " << char(m.to.second + 65) << m.to.first + 1;
	if (m.captured_name != Piece::get_empty()->get_name())
		std::cout << " and captures piece " << m.captured_name;
	std::cout << "." << std::endl;
}

void printer::print_intro()
{
	std::cout
		<< "Hello and welcome to RandomChess!  This is a simple Chess simulator, created by Enya Zimecka," << std::endl
		<< "with an opponent who moves uniformly at random." << std::endl
		<< std::endl;
}

void printer::print_pairs(std::vector<std::pair<int, int>> pairs)
{
	std::cout << "printing pairs:" << std::endl;
	for (std::pair<int, int> p : pairs)
	{
		std::cout << "(" << p.first << "," << p.second << ")," << std::endl;
	}
}

void printer::print_win()
{
	std::cout << std::endl << "Checkmate, you win!  Type 'again' if you want to play again or 'quit' to quit." << std::endl;
}

void printer::print_lose()
{
	std::cout << std::endl << "Checkmate, you lose!  Better luck next time!  Type 'again' if you want to play" << std::endl
		<< "again or 'quit' to quit." << std::endl;
}