#include "queen.hpp"

#include "board.hpp"

#include <algorithm>

extern Board B;

std::vector<std::pair<int,int>> Queen::get_valid_moves()
{
    // The Queen has the sum of the movement rules of the Rook and the Bishop
    std::vector<std::pair<int,int>> horiz_vert_moves = ((Rook*)this)->get_valid_moves(),
                                    diagonal_moves = ((Bishop*)this)->get_valid_moves();

    // STL algorithm
    std::insert(horiz_vert_moves.begin(),
                   diagonal_moves.begin(),
                   diagonal_moves.end();

    return horiz_vert_moves;
}