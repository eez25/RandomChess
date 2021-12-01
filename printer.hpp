#pragma once

#include <vector>
#include <string>

// namespace encapsulates the specific printer methods we made
namespace printer {
    void print_board(Board b);

    void print_prompt();

    void print_horiz();

    void print_row(std::vector<Piece*> row);

    void print_col_names();

    //void print_cant_do(move m);

    //void print_comp_move(move m);
}
