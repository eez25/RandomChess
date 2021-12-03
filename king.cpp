#include "king.hpp"

#include "board.hpp"

extern Board Bd;

std::vector<std::pair<int,int>> King::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;

    //look at all the spaces within a width-three square centered at this Piece's square
    for(int r_mod = -1; r_mod < 2; r_mod++)
    {
        for(int c_mod = -1; c_mod < 2; c_mod++)
        {
            // if the space we're looking at is the space of our current piece, continue to the next space
            if(r_mod == 0 && c_mod == 0) continue;

            // update moves if we can
            check_valid(&moves, get_position().first + r_mod, get_position().second + c_mod);
        }
    }

    return moves;
}