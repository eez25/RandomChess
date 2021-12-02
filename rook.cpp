#include "rook.hpp"

#include "board.hpp"

extern Board B;

std::vector<std::pair<int,int>> Rook::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;

    // a Rook can move to the right until it meets a piece, and can capture it if it is an enemy
    int c = get_position().second;
    for (int r = get_position().first + 1; r < BOARD_LENGTH; r++)
    {
        if(check_valid(&moves,r,c)) break;
    }

    // the same, to the left instead
    for (int r = get_position().first - 1; r >= 0; r--)
    {
        if(check_valid(&moves,r,c)) break;
    }

    // the same, up the board
    int r = get_position().first;
    for (int c = get_position().second + 1; c < BOARD_LENGTH; c++)
    {
        if(check_valid(&moves,r,c)) break;
    }

    // the same, down the board
    for (int c = get_position().second - 1; c > 0; c--)
    {
        if(check_valid(&moves,r,c)) break;
    }

    return moves;
}