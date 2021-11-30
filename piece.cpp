#include "piece.hpp"

#include <algorithm>
#include <random>

std::string Piece::get_name()
{
    return name;
}

bool Piece::get_team()
{
    return team;
}

std::vector<std::pair<int,int>> Piece::get_valid_moves()
{
    //TODO after making board
}

void Piece::move(std::pair<int,int> coords)
{
    //TODO after making board
}

void Piece::random_move()
{
    std::vector<std::pair<int,int>> m, possible_moves;
    possible_moves = get_valid_moves();
    std::sample(possible_moves.begin(),possible_moves.end(),m,1,std::random_device{}());
    move(m[0]);
}