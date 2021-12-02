#include "piece.hpp"

class Pawn : public Piece 
{
    public:
        //constructor
        Pawn(Team team, int r, col c) : Piece(PType::P, team, std::pair(r,(int)c)){}

        std::vector<std::pair<int,int>> get_valid_moves();
};