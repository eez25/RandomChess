#include "piece.hpp"

#include <algorithm>
#include <random>
#include <iostream>

#include "board.hpp"

extern Board B;

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

Piece* Piece::empty = &Piece(PType::Empty,Team::Empty, std::pair(-1,-1));

Piece* Piece::get_empty()
{
    return empty;
}

int Piece::forward()
{
    switch (team){
        case Team::Empty:
            return 0;
        case White:
            return 1;
        case Black:
            return -1;
    }
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
            case P:
                name = team == White? "P" : "p";
                break;
            case R:
                name = team == White? "R" : "r";
                break;
            case N:
                name = team == White? "N" : "n";
                break;
            case PType::B:
                name = team == White? "B" : "b";
                break;
            case K:
                name = team == White? "K" : "k";
                break;
            case Q:
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
    position = p;
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
    std::cout << "THIS METHOD SHOULD NEVER BE CALLED: Piece::get_valid_moves()";
    std::vector<std::pair<int,int>> moves;
    return moves;
}

bool Piece::move(std::pair<int,int> coords)
{
    std::vector<std::pair<int,int>> valid_moves = get_valid_moves();

    // STL algorithm
    // return false if the move is invalid
    if (std::count(valid_moves.begin(),valid_moves.end(),coords) == 0) return false;

    // if the move is valid:
    B.move(this,coords);

    return true;
}

void Piece::random_move()
{
    std::vector<std::pair<int,int>> m, 
                                    possible_moves = get_valid_moves();
    // STL algorithm
    // pick a random move from the list of possible ones
    std::sample(possible_moves.begin(),possible_moves.end(),m,1,std::random_device{}());

    move(m[0]);
}

bool Piece::is_threatening(std::pair<int,int> pos)
{
    std::vector<std::pair<int,int>> valid_moves = get_valid_moves();

    // true if this piece can move to this position on the board
    return std::count(valid_moves.begin(),valid_moves.end(),pos) > 0;
}

bool Piece::check_valid(std::vector<std::pair<int,int>>* moves, int r, int c)
{
    // if there is no piece there
    if(B.board[r][c] == Piece::get_empty())
        {
            moves->emplace_back(r,c);
            return false;

        // if there is already piece here, this piece can move here if they are enemies
        } else { 
            if(B.board[r][c]->get_team() == opposite(get_team()))
                moves->emplace_back(r,c);
            return true;
        }
}