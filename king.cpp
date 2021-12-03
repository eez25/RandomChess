#include "king.hpp"

#include "board.hpp"

extern Board Bd;

std::vector<std::pair<int,int>> King::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;
    int r = get_position().first,
        c = get_position().second;

    //look at all the spaces within a width-three square centered at this Piece's square
    for(int loop_r = r-1; loop_r < r+2; loop_r++)
    {
        for(int loop_c = c-1; loop_c < c-2; loop_c++)
        {
            // if the space we're looking at is the space of our current piece, continue to the next space
            if(loop_r == r && loop_c == c) continue;

            // if the space we're looking at is not on the board, continue to the next space
            if (Board::off_board(loop_r, loop_c)) continue;

            // update moves if we can
            check_valid(&moves, loop_r, loop_c);
        }
    }

    return moves;
}