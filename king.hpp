#include "piece.hpp"

class King : public Piece 
{
    public:
        //constructor
        King(Team team, std::pair<int,int> pos) : Piece(PType::King, team, pos){}

        std::vector<std::pair<int,int>> get_valid_moves();
};