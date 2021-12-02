#include "piece.hpp"

class Pawn : public Piece 
{
    public:
        //constructor
        Pawn(Team team, std::pair<int,int> pos) : Piece(PType::Pawn, team, pos){}

        std::vector<std::pair<int,int>> get_valid_moves();
};