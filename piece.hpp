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
    King = 5,
    Empty = 6
};

enum Team 
{
    White = 0,
    Black = 1,
    Empty = 2
};

class Piece
{
    private:
        std::string name;
        Team team;
        PType type;
        std::pair<int,int> position;
        static Piece* empty;

    public:
        //initializer
        Piece(PType type, Team team, std::pair<int,int> position);

        //returns a pointer to an empty Piece placeholder
        static Piece* get_empty();

        //getters
        std::string get_name();
        Team get_team();
        PType get_type();
        std::pair<int,int> get_position();

        //setter; returns false if another piece is already there
        bool set_position(std::pair<int,int> p);

        //returns the opposite team
        static Team opposite(Team t);

        //Operator overloads
        int operator == (Piece p);
        int operator == (std::pair<PType,Team> t);

        //returns a vector of the possible moves that can be made
        std::vector<std::pair<int,int>> get_valid_moves();

        //moves a piece and handles chain reactions of other pieces needing to be removed, etc.
        void move(std::pair<int,int> coords);

        //moves a piece to a valid location chosen uniformly at random
        void random_move();

        //returns true if this piece is threatening the square at pos
        bool is_threatening(std::pair<int,int> pos);
};