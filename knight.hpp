#include "piece.hpp"

class Knight : public Piece 
{
    public:
        //constructor
        Knight(Team team, std::pair<int,int> pos) : Piece(PType::Knight, team, pos){}

        std::vector<std::pair<int,int>> get_valid_moves();
};