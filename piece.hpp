#pragma once

#include <string>
#include <vector>

enum PType 
{
    P = 0, // Pawn
    R = 1, // Rook
    N = 2, // kNight
    B = 3, // Bishop
    Q = 4, // Queen
    K = 5, // King
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
        // constructor
        Piece(PType type, Team team, std::pair<int,int> position);
        Piece() = default;

        // returns a pointer to an empty Piece placeholder
        static Piece* get_empty();

        // returns 1 if the forward direction of this Piece's Team is positive or -1 if that is in the forward direction
        int forward();

        // getters
        std::string get_name();
        Team get_team();
        PType get_type();
        std::pair<int,int> get_position();

        // setter; returns false if another piece is already there
        bool set_position(std::pair<int,int> p);

        // returns the opposite team
        static Team opposite(Team t);

        // Operator overloads
        int operator == (Piece p);
        int operator == (std::pair<PType,Team> t);

        // returns a vector of the possible moves that can be made
        virtual std::vector<std::pair<int,int>> get_valid_moves();

        /* moves a piece and handles chain reactions of other pieces needing to be removed, etc.
         * returns false if the move is invalid */
        bool move(std::pair<int,int> coords);

        // moves a piece to a valid location chosen uniformly at random
        void random_move();

        // returns true if this piece is threatening the square at pos
        bool is_threatening(std::pair<int,int> pos);

        /* updates moves with the pair (r,c) if it is not occupied by a teammate piece;
         * returns true if there is already a piece there, enemy or not */
        bool check_valid(std::vector<std::pair<int,int>>* moves, int r, int c);
};