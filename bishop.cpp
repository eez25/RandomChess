#include "bishop.hpp"

#include "board.hpp"

extern Board B;

std::vector<std::pair<int,int>> Bishop::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;

    int r = get_position().first, c = get_position().second;

    // a Bishop can move diagonally until it meets another piece, and can 
    // capture it if it's an enemy

    // check the positive, positive direction
    for (int i = 1; i < std::min(BOARD_LENGTH-r, BOARD_LENGTH-c); i++)
    {
        if(check_valid(&moves,r+i,c+1)) break;
    }

    // check the negative, negative direction
    for (int i = 1; i < std::min(r,c); i++)
    {
        if(check_valid(&moves,r-i,c-i)) break;
    }

    // check the positive, negative direction
    for (int i = 1; i < std::min(BOARD_LENGTH-r, c); i++)
    {
        if(check_valid(&moves,r+i,c-i)) break;
    }

    // check the negative, positive direction
    for (int i = 1; i < std::min(r, BOARD_LENGTH-c); i++)
    {
        if(check_valid(&moves,r-i,c+i)) break;
    }

    return moves;
}