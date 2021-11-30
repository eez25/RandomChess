#pragma once

#include <string>
#include <vector>

enum PType 
{
    Pawn = 0,
    Rook = 1,
    Knight = 2,
    Bishop = 3,
    Queen = 4,
    King = 5
};

enum Team 
{
    White = true,
    Black = false
};

class Piece
{
    private:
        std::string name;
        Team team;
        PType type;
        std::pair<int,int> position;

    public:
        std::string get_name();
        Team get_team();
        PType get_type();
        std::pair<int,int> get_position();
        int operator == (Piece p);
        std::vector<std::pair<int,int>> get_valid_moves();
        void move(std::pair<int,int> coords);
        void random_move();
};