#include <iostream>

#include "board.hpp"

#include "printer.hpp"

void print_board(Board b)
{
    print_col_names();
    print_horiz();
    for (int i = 7; i >= 0; i--)
    {
        std::cout << " " << i+1; print_row(b.board[i]); std::cout << " " << i+1 << std::endl;
        print_horiz();
    }
    print_col_names();
}

/* prints a horizontal line */
void print_horiz()
{
    std::cout << "   +---+---+---+---+---+---+---+---+" << std::endl;
}

void print_col_names()
{
    std::cout << "     A   B   C   D   E   F   G   H  " << std::endl;
}

/* prints a single row of the board, including the pieces currently present on it */
void print_row(std::vector<Piece*> row)
{
    for (Piece* p : row)
    {
        std:: cout << " | " << p->get_name();
    }
    std::cout << " |";
}

/* The below was and can be used for unit testing of this printer */

// std::vector<std::vector<std::string>> test = {{"","","K","","","","",""},
//                                               {"","","","","","","",""},
//                                               {"","","","","","","",""},
//                                               {"","","","","","","",""},
//                                               {"","","9","","","","",""},
//                                               {"","","","","","","",""},
//                                               {"","","","","P","","",""},
//                                               {"","","","","","","",""}};

// int main(){
//     print_board(test);
//     return 0;
// }