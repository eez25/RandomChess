#include "piece.hpp"

#include <algorithm>
#include <random>

std::string Piece::get_name()
{
    return name;
}

Team Piece::get_team()
{
    return team;
}

PType Piece::get_type()
{
    return type;
}

std::pair<int,int> Piece::get_position()
{
    return position;
}

// Overloaded operator
int Piece::operator == (Piece p)
{
    return (p.get_team() == team && p.get_type() == type);
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
    // STL algorithm:
    std::sample(possible_moves.begin(),possible_moves.end(),m,1,std::random_device{}());
    move(m[0]);
}