#pragma once

#include <vector>
#include <string>

#include "move.hpp"

// namespace encapsulates the specific printer methods we made
namespace printer {
    void print_board(Board b);

    void print_prompt();

    void print_horiz();

    void print_row(std::vector<Piece*> row);

    void print_col_names();

    void print_cant_do();

    void print_comp_move(Move m);

    void print_intro();

    void print_help();

    void print_pairs(std::vector<std::pair<int,int>> pairs);

    void print_win();

    void print_lose();
}
