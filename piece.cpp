#include "piece.hpp"

#include <algorithm>
#include <random>

Team opposite(Team t)
{
    switch(t)
    {
        case Team::Empty:
            return Empty;
        case White:
            return Black;
        case Black:
            return White;
    }
}

//utilizes enum class names similar to namespaces
Piece* Piece::empty = &Piece(PType::Empty,Team::Empty, std::pair(-1,-1));

Piece* Piece::get_empty()
{
    return empty;
}

Piece::Piece(PType type, Team team, std::pair<int,int> position) :
    type(type),
    team(team),
    position(position)
    {
        switch (type){
            case PType::Empty:
                name = " ";
                break;
            case Pawn:
                name = team == White? "P" : "p";
                break;
            case Rook:
                name = team == White? "R" : "r";
                break;
            case Knight:
                name = team == White? "N" : "n";
                break;
            case Bishop:
                name = team == White? "B" : "b";
                break;
            case King:
                name = team == White? "K" : "k";
                break;
            case Queen:
                name = team == White? "Q" : "q";
                break;
        } 
    }

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

bool Piece::set_position(std::pair<int,int> p)
{

}

// Overloaded operator
int Piece::operator == (Piece p)
{
    return (p.get_team() == team && p.get_type() == type);
}

int Piece::operator == (std::pair<PType,Team> t)
{
    return (type == t.first && team == t.second);
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

bool Piece::is_threatening(std::pair<int,int> pos)
{
    std::vector<std::pair<int,int>> valid_moves = get_valid_moves();
    return std::count(valid_moves.begin(),valid_moves.end(),pos) > 0;
}