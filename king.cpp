#include "king.hpp"

#include "board.hpp"

extern Board Bd;

std::vector<std::pair<int,int>> King::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;
    int r = get_position().first,
        c = get_position().second;
    
    bool threatened;

    //look at all the spaces within a width-three square centered at this Piece's square
    for(int loop_r = r-1; loop_r < r+2; loop_r++)
    {
        for(int loop_c = c-1; loop_c < c-2; loop_c++)
        {
            threatened = false;

            // if the space we're looking at is the space of our current piece, continue to the next space
            if(loop_r == r && loop_c == c) continue;

            // if the space we're looking at is not on the board, continue to the next space
            if (Board::off_board(loop_r, loop_c)) continue;

            // check if any opposing piece is threatening this square
            for (Piece* possible_threatener : Bd.get_checking_pieces(Piece::opposite(get_team())))
            {
                if (possible_threatener->is_threatening(std::pair(loop_r, loop_c)))
                {
                    threatened = true;
                    break;
                }
            }

            // only if the square is not threatened can the king possibly move there
            if (not threatened) check_valid(&moves, loop_r, loop_c);
        }
    }

    return moves;
}

std::vector<std::pair<int, int>> King::get_blockables()
{
    // a king cannot threaten another king because it would force him to threaten himself
    std::vector<std::pair<int, int>> blockables;
    return blockables;
}