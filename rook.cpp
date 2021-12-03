#include "rook.hpp"

#include "board.hpp"

#include <iostream>

extern Board Bd;

std::vector<std::pair<int,int>> Rook::get_valid_moves()
{
    std::vector<std::pair<int,int>> moves;

    // a Rook can move up the board until it meets a piece, and can capture it if it is an enemy
    int c = get_position().second;
    for (int r = get_position().first + 1; r < BOARD_LENGTH; r++)
    {
        std::cout << std::endl << "checking if the rook can move up the board (" << r << "," << c << ") ";
        if(check_valid(&moves,r,c)) { std::cout << "no"; break; }
        std::cout << "yes";
    }

    // the same, down the board
    for (int r = get_position().first - 1; r >= 0; r--)
    {
        std::cout << std::endl << "checking if the rook can move down the board (" << r << "," << c << ") ";
        if (check_valid(&moves, r, c)) { std::cout << "no"; break; }
        std::cout << "yes";
    }

    // the same, to the right
    int r = get_position().first;
    for (int c = get_position().second + 1; c < BOARD_LENGTH; c++)
    {
        std::cout << std::endl << "checking if the rook can move to the right (" << r << "," << c << ") ";
        if (check_valid(&moves, r, c)) { std::cout << "no"; break; }
        std::cout << "yes";
    }

    // the same, down the board
    for (int c = get_position().second - 1; c >= 0; c--)
    {
        std::cout << std::endl << "checking if the rook can move to the left (" << r << "," << c << ") ";
        if (check_valid(&moves, r, c)) { std::cout << "no"; break; }
        std::cout << "yes";
    }
    std::cout << std::endl;

    return moves;
}