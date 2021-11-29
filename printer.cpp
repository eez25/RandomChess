#include <iostream>

#include "printer.hpp"

void print_board(std::vector<std::vector<std::string>> board)
{
    print_col_names();
    print_horiz();
    for (int i = 7; i >= 0; i--)
    {
        std::cout << " " << i+1; print_row(board[i]); std::cout << " " << i+1 << std::endl;
        print_horiz();
    }
    print_col_names();
}

void print_horiz()
{
    std::cout << "   +---+---+---+---+---+---+---+---+" << std::endl;
}

void print_col_names()
{
    std::cout << "     A   B   C   D   E   F   G   H  " << std::endl;
}

void print_row(std::vector<std::string> row)
{
    for (std::string p : row)
    {
        std:: cout << " | " << (p.empty()? " " : p);
    }
    std::cout << " |";
}

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